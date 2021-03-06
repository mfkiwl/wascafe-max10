#include <stdio.h>

#include "spi_max10.h"

#include <string.h>
#include "log.h"

/* External definitions for our SPI interface. */
extern SPI_HandleTypeDef hspi2;
extern DMA_HandleTypeDef hdma_spi2_rx;
extern DMA_HandleTypeDef hdma_spi2_tx;

/* Enable below to output logs for SPI debug. */
#define SPI_DEBUG_LOGS 0

#if SPI_DEBUG_LOGS == 1
#   define spi_logout(...) termout(WL_LOG_DEBUGNORMAL, __VA_ARGS__)
#else // SPI_DEBUG_LOGS
#   define spi_logout(...)
#endif // !SPI_DEBUG_LOGS

/* Output error messages to UART without consideration
 * of the log output setting above
 */
#define spi_error_out(...) termout(WL_LOG_DEBUGNORMAL, __VA_ARGS__)



/* Global variable indicating SPI communication state.
 * This is shared between SPI interrupt handler
 * and main routines.
 */
#define SPI_STATE_PREPARE_RCV   0
#define SPI_STATE_RCV_IDLE      1
#define SPI_STATE_MSGPROC_START 2
#define SPI_STATE_MSGPROC_DONE  3
#define SPI_STATE_SEND_RESPONSE 4
#define SPI_STATE_SEND_IDLE     5

int _spi_state = SPI_STATE_PREPARE_RCV;

/* SPI state machine update. */
void spi_update_state(int spi_state);



void SPI_IRQHandler(void)
{
    /* USER CODE BEGIN SPI1_IRQn 0 */
    spi_logout("^^^ Tick[0x%08X] SPI_IRQHandler STT", (unsigned int)HAL_GetTick());
    /* USER CODE END SPI1_IRQn 0 */

    HAL_SPI_IRQHandler(&hspi2);

    /* USER CODE BEGIN SPI1_IRQn 1 */
    spi_logout("^^^ Tick[0x%08X] SPI_IRQHandler STT", (unsigned int)HAL_GetTick());
    /* USER CODE END SPI1_IRQn 1 */
}

// https://stm32f4-discovery.net/2014/08/stm32f4-external-interrupts-tutorial/
// http://www.lxtronic.com/index.php/basic-spi-simple-read-write

/* The buffer for latest completely received header. */
wl_spi_trans_hdr_t _spi_trans_hdr;

/* Rx/Tx work buffers. */
wl_spi_trans_hdr_t _spi_trans_hdr_rx;
wl_spi_trans_hdr_t _spi_trans_hdr_tx;



/* SPI flow control macros.
 * For internal use here only.
 */
#define SPI_MAX10_RCV_HDR_READY() HAL_GPIO_WritePin(GPIOA, SPI_SYNC_Pin, GPIO_PIN_RESET)
#define SPI_MAX10_SND_RSP_READY() HAL_GPIO_WritePin(GPIOA, SPI_SYNC_Pin, GPIO_PIN_SET  )



unsigned char char2pchar(unsigned char c)
{
    /* Display differently null and FF characters.
     * It helps to spot them in screen full of hexa codes.
     */
    if(c == 0x00) return '~';
    if(c == 0xFF) return 'X';

    /* Non-displayable characters. */
    if(c < ' ') return '.';
    if(c > 127) return '?';

    return c;
}


void spi_init(void)
{
//    /* Prevent from receiving data while transaction header isn't yet processed. */
//    HAL_GPIO_WritePin(GPIOA, SPI_SYNC_Pin, GPIO_PIN_RESET);

    /* Reset the internals. */
    memset(&_spi_trans_hdr, 0, sizeof(wl_spi_trans_hdr_t));
    memset(&_spi_trans_hdr_rx, 0, sizeof(wl_spi_trans_hdr_t));
    memset(&_spi_trans_hdr_tx, 0, sizeof(wl_spi_trans_hdr_t));

    /* Prepare reception of first transmission header. */
    _spi_state = SPI_STATE_PREPARE_RCV;
    spi_update_state(_spi_state);
}


/* Simple function to translate memory alias.
 * Note : handles only translation to physical
 *        address : logs access etc must be
 *        implemented separately.
 */
unsigned long spi_memacc_translate(wl_spicomm_memacc_t* param)
{
    unsigned long addr_prefix = param->addr >> 24;
    unsigned long addr_tmp;

    switch(addr_prefix)
    {
    /* STM32 Flash ROM, first 1MB. */
    case(((WL_STADR_FLASH) >> 24) + 0x00):
        addr_tmp = param->addr & 0x00FFFFFF;
        addr_tmp += 0x08000000;
        param->addr = addr_tmp;
        break;
    /* STM32 Flash ROM, second 1MB. */
    case(((WL_STADR_FLASH) >> 24) + 0x01):
        addr_tmp = param->addr & 0x00FFFFFF;
        addr_tmp += 0x08100000;
        param->addr = addr_tmp;
        break;

    /* SRAM. */
    case((WL_STADR_SRAM) >> 24):
        addr_tmp = param->addr & 0x00FFFFFF;
        addr_tmp += 0x20000000;
        param->addr = addr_tmp;
        break;

    /* Direct access, or alias unsupported here. */
    default:
        break;
    }

    /* Return address prefix, so that caller
     * can do whatever they want with it.
     */
    return addr_prefix;
}




void HAL_SPI_RxTxCpltCallback(SPI_HandleTypeDef* hspi)
{
    spi_logout("Tick[0x%08X][%s::%d] HAL_SPI_RxTxCpltCallback called"
        , (unsigned int)HAL_GetTick()
        , __FILE__, __LINE__);
}


//void HAL_SPI_RxHalfCpltCallback (SPI_HandleTypeDef *hspi)
//{
//    spi_logout("Tick[0x%08X][%s::%d] HAL_SPI_RxHalfCpltCallback called"
//        , (unsigned int)HAL_GetTick()
//        , __FILE__, __LINE__);
//}


void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef* hspi)
{
    spi_logout("Tick[0x%08X][%s::%d] HAL_SPI_TxCpltCallback called state[%d]"
        , (unsigned int)HAL_GetTick()
        , __FILE__, __LINE__
        , _spi_state);

    /* Indicate that SPI must be re-init for next transation.
     * We are currently in interrupt handler, and this must be
     * done on main module side, hence the trick below with
     * global variable.
     */
    _spi_state = SPI_STATE_PREPARE_RCV;
}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef* hspi)
{
    spi_logout("Tick[0x%08X][%s::%d] HAL_SPI_RxCpltCallback called state[%d]"
        , (unsigned int)HAL_GetTick()
        , __FILE__, __LINE__
        , _spi_state);

    wl_spi_trans_hdr_t* trans_hdr = &_spi_trans_hdr;

    if(_spi_trans_hdr_rx.cmn.magic_ca == 0xCA)
    {
        memcpy(trans_hdr, &_spi_trans_hdr_rx, sizeof(wl_spi_trans_hdr_t));
    }
    else
    {
        /* Dirty tweak ... */
        unsigned short* dst = (unsigned short*)trans_hdr;
        unsigned short* src = (unsigned short*)&_spi_trans_hdr_rx;
        for(int i=0; i<((sizeof(wl_spi_trans_hdr_t)-1) / sizeof(unsigned short)); i++)
        {
            dst[i] = src[i+1];
        }
    }

    /* Log transmission header contents. */
    spi_logout("*** magic:%02X %02X, len:%u"
        , trans_hdr->cmn.magic_ca
        , trans_hdr->cmn.magic_fe
        , trans_hdr->cmn.pkt_len);

    if((trans_hdr->cmn.magic_ca != 0xCA)
    && (trans_hdr->cmn.magic_fe != 0xFE))
    {
        spi_error_out("*** SPI ERROR *** Invalid header ! magic:%02X %02X, len:%u"
            , trans_hdr->cmn.magic_ca
            , trans_hdr->cmn.magic_fe
            , trans_hdr->cmn.pkt_len);
        for(int i=0; i<16; i++)
        {
            unsigned char* ptr = (unsigned char*)trans_hdr;
            spi_error_out("| Rcv[%3d]:0x%02X (%c)", i, ptr[i], ptr[i]);
        }

        _spi_state = SPI_STATE_PREPARE_RCV;
        return;
    }


    if(_spi_state == SPI_STATE_RCV_IDLE)
    { /* Finished to receive packet from MAX10 : will prepare answer packet outside of this IRQ handler. */
        _spi_state = SPI_STATE_MSGPROC_START;
    }
    else if(_spi_state == SPI_STATE_MSGPROC_DONE)
    { /* Answered back to MAX 10. */
    }
    else
    { /* Finished to send back packet to MAX10 : prepare for receiving next packet. */
        spi_logout("HAL_SPI_Transmit END PARAMS");

        _spi_state = SPI_STATE_PREPARE_RCV;
    }
}


void spi_send_answer(void)
{
    wl_spi_trans_hdr_t* pkt_tx = &_spi_trans_hdr_tx;
    wl_spi_trans_hdr_t* trans_hdr = &_spi_trans_hdr;

    /* Copy back header from Rx to Tx buffer. */
    memcpy(&(pkt_tx->cmn), &(trans_hdr->cmn), sizeof(wl_spi_common_hdr_t));

    /******************************************/
    /* Prepare response for sending to MAX10. */
    spi_logout("Tick[0x%08X] CMD[0x%02X]", (unsigned int)HAL_GetTick(), trans_hdr->cmn.command);

    if(trans_hdr->cmn.command == WL_SPICMD_VERSION)
    { /* STM32 firmware version. */
        wl_spicomm_version_t* ver = (wl_spicomm_version_t*)pkt_tx->params;
        char* build_date = __DATE__;
        char* build_time = __TIME__;

        memset(ver, 0, sizeof(wl_verinfo_t));

        /* Write firmware build date and time. */
        strcpy(ver->build_date, build_date);
        strcpy(ver->build_time, build_time);

        spi_logout("Tick[0x%08X] Version[%s][%s]", (unsigned int)HAL_GetTick(), ver->build_date, ver->build_time);
    }
    else if(trans_hdr->cmn.command == WL_SPICMD_MEMREAD)
    { /* STM32 memory/registers read. */
        wl_spicomm_memacc_t* rd_params = (wl_spicomm_memacc_t*)trans_hdr->params;

        /* Translate address alias. */
        unsigned long addr_prefix = spi_memacc_translate(rd_params);

        spi_logout("Tick[0x%08X] MemRead[0x%08X][%u]", (unsigned int)HAL_GetTick(), (unsigned int)rd_params->addr, rd_params->len);

        if(addr_prefix == (WL_STADR_LOGS_FIFO >> 24))
        {
            /* Special alias when reading logs from circular buffer :
             *  - Address is ignored and logs data
             *    are read from start of circular buffer.
             *  - Read data size is limited to amount
             *    of data available in circular buffer.
             *
             * Additionally, special alias at offset 0x01_0000
             * returns amount of data into circular buffer without
             * touching its contents.
             */
            if(rd_params->addr == WL_STADR_LOGS_STAT)
            {
                 memset(pkt_tx->params, 0x00, rd_params->len);

                if(rd_params->len == sizeof(wla_logs_stats_t))
                {
                    /* Return logs circular buffer status. */
                    wla_logs_stats_t* st = (wla_logs_stats_t*)pkt_tx->params;

                    //spi_logout("@@@ Tick[0x%08X] log_cbmem_use:%5u"
                    //    , (unsigned int)HAL_GetTick()
                    //    , (unsigned int)log_cbmem_use());

                    st->buffer_size = log_cbmem_total();
                    st->usage       = log_cbmem_use();
                 }
            }
            else
            {
                /* Read logs from circular buffer. */
                unsigned short read_len = log_cbmem_use();
                // spi_logout("@@@ Tick[0x%08X] logs_cb_read:%5u, len:%5u"
                //     , (unsigned int)HAL_GetTick()
                //     , (unsigned int)read_len
                //     , (unsigned int)rd_params->len);

                if(rd_params->len < read_len)
                {
                   read_len = rd_params->len;
                }

                memset(pkt_tx->params, 'P', rd_params->len);
                log_cbread(pkt_tx->params, read_len, 1/*update_rp*/);
             }
        }
        else
        {
            /* Direct read from specified (physical or alias) address. */
            memcpy(pkt_tx->params, (void*)(rd_params->addr), rd_params->len);
        }
    }
    else if(trans_hdr->cmn.command == WL_SPICMD_MEMWRITE)
    { /* STM32 memory/registers write. */
        wl_spicomm_memacc_t* wr_params = (wl_spicomm_memacc_t*)trans_hdr->params;
        unsigned char* wr_data = trans_hdr->params + sizeof(wl_spicomm_memacc_t);

        /* Translate address alias. */
        spi_memacc_translate(wr_params);

        spi_logout("Tick[0x%08X] MemWrite[0x%08X][%u] Data[0x%02X %02X %02X %02x ...]", 
            (unsigned int)HAL_GetTick(), 
            (unsigned int)wr_params->addr, wr_params->len, 
            (unsigned int)(wr_data[0]), (unsigned int)(wr_data[1]), (unsigned int)(wr_data[2]), (unsigned int)(wr_data[3]));

        memcpy((void*)(wr_params->addr), wr_data, wr_params->len);
    }
    else
    { /* Dummy answer. */

        pkt_tx->cmn.command = WL_SPICMD_DUMMY;

        pkt_tx->params[WL_SPI_PARAMS_LEN - 1] = '\0';

        spi_logout("HAL_SPI_Receive PARAMS[%s]", (char*)(trans_hdr->params));

        unsigned char answer_tmp[WL_SPI_PARAMS_LEN];
        memset(answer_tmp, 0, WL_SPI_PARAMS_LEN * sizeof(unsigned char));
        pkt_tx->params[WL_SPI_PARAMS_LEN / 2] = '\0'; /* Should be enough for storing both messages from MAX10 and STM32. */
        sprintf((char*)answer_tmp, "Tick[%08X][%02X%02X%02X%02X][%s]Hello, this is STM32, hope you are well."
            , (unsigned int)HAL_GetTick()
            , pkt_tx->end_bytes[0]
            , pkt_tx->end_bytes[1]
            , pkt_tx->end_bytes[2]
            , pkt_tx->end_bytes[3]
            , (char*)pkt_tx->params);
        memcpy(pkt_tx->params, answer_tmp, WL_SPI_PARAMS_LEN * sizeof(unsigned char));
        pkt_tx->params[WL_SPI_PARAMS_LEN - 1] = '\0';
        pkt_tx->end_bytes[0] = 0x51;
        pkt_tx->end_bytes[1] = 0x52;
        pkt_tx->end_bytes[2] = 0x53;
        pkt_tx->end_bytes[3] = 0x54;
    }

    spi_logout("Tick[0x%08X]Response str[%s]"
        , (unsigned int)HAL_GetTick()
        , (char*)(pkt_tx->params));


    /* Indicate that SPI must be re-init for next transation.
     * We are currently in interrupt handler, and this must be
     * done on main module side, hence the trick below with
     * global variable.
     */
    _spi_state = SPI_STATE_SEND_RESPONSE;
}


void spi_update_state(int spi_state)
{
    spi_logout("@@@ Tick[0x%08X] spi_update_state[%d]"
        , (unsigned int)HAL_GetTick()
        , spi_state);


    if(spi_state == SPI_STATE_PREPARE_RCV)
    {
        /* Goto next state. */
        _spi_state = SPI_STATE_RCV_IDLE;

        if(HAL_SPI_Receive_DMA(&hspi2, (uint8_t*)(&_spi_trans_hdr_rx), sizeof(wl_spi_trans_hdr_t) / sizeof(unsigned short)) != HAL_OK)
        {
            Error_Handler();
        }

        /* Indicate that we are ready to receive header. */
        SPI_MAX10_RCV_HDR_READY();
    }
    else if(spi_state == SPI_STATE_SEND_RESPONSE)
    {
        /* Goto next state. */
        _spi_state = SPI_STATE_SEND_IDLE;

        /* Output message about to send to UART. */
        if(_spi_trans_hdr_tx.params[ 4] == '0')
        {
            spi_logout("[SPI_Transmit_DMA]pkt_len:%4u params[%c%c%c%c][%c%c%c%c][%c%c%c%c]\r\n",
                _spi_trans_hdr_tx.cmn.pkt_len, 
                char2pchar(_spi_trans_hdr_tx.params[ 0]), char2pchar(_spi_trans_hdr_tx.params[ 1]), char2pchar(_spi_trans_hdr_tx.params[ 2]), char2pchar(_spi_trans_hdr_tx.params[ 3]), 
                char2pchar(_spi_trans_hdr_tx.params[ 4]), char2pchar(_spi_trans_hdr_tx.params[ 5]), char2pchar(_spi_trans_hdr_tx.params[ 6]), char2pchar(_spi_trans_hdr_tx.params[ 7]), 
                char2pchar(_spi_trans_hdr_tx.params[ 8]), char2pchar(_spi_trans_hdr_tx.params[ 9]), char2pchar(_spi_trans_hdr_tx.params[10]), char2pchar(_spi_trans_hdr_tx.params[11])
            );
        }


        if(HAL_SPI_Transmit_DMA(&hspi2, (uint8_t*)(&_spi_trans_hdr_tx), sizeof(wl_spi_trans_hdr_t) / sizeof(unsigned short)) != HAL_OK)
        {
            Error_Handler();
        }

        /* Indicate that we are ready to send response. */
        SPI_MAX10_SND_RSP_READY();

        spi_logout("Tick[0x%08X]Send response header END", (unsigned int)HAL_GetTick());
    }
}


int spi_periodic_check(void)
{
    int ret = 0;

    /* If packet received from MAX 10, then process its answer. */
    if(_spi_state == SPI_STATE_MSGPROC_START)
    {
        spi_send_answer();
    }

    /* If required, re-init SPI state. */
    int spi_state = _spi_state;
    if((spi_state == SPI_STATE_PREPARE_RCV)
    || (spi_state == SPI_STATE_SEND_RESPONSE))
    {
        spi_update_state(spi_state);

        if(spi_state == SPI_STATE_PREPARE_RCV)
        {
            ret = 1;
        }
    }

    return ret;
}

