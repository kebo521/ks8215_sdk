void EMVProcessCallback(u8* data)
{
    if (data[0] == STATUS_COMPLETION)
    {
    	switch (data[1])
    	{
            case APPROVE_OFFLINE:
                //TODO
                break;
            case APPROVE_ONLINE:
                //TODO
                break;
            case DECLINE_OFFLINE:
                //TODO
                break;
            case DECLINE_ONLINE:
                //TODO
                break;
            case FALLBACK:
                //TODO
                break;
            default:
                break;
    	}

    }
    else if (data[0] == STATUS_CONTINUE)
    {
        //TODO
    }
    else if (data[0] == STATUS_ERROR)
    {
        //TODO
    }
}

void CardEventOccured(int type)
{
    
}

const EMV_PORTING g_emv_porting =
{
    .EMVProcessCallback = EMVProcessCallback,
    .CardEventOccured = CardEventOccured,
}

int main(void)
{
    int ret;
    
	emv_initialize(&g_emv_porting); //上电一次就可以

//交易开始

    emv_set_trans_type(EMV_TRANSTYPE_GOODS_SERVICES);
    
    emv_set_trans_amount(100);
    emv_set_other_amount(0);

    emv_preprocess(); //QPBOC

    //TODO 巡卡

    emv_set_cardtype(EMV_CARD_CONTACTLESS);


    while (1)
    {
        ret = emv_process();
        if (ret < 0) return;
        
        switch (ret)
        {
            case EMV_REQ_GO_ONLINE:
                //TODO 联机
                emv_set_online_result(int result, u8 * resp, int resp_len);
                break;
                
              
        }
    }

    emv_process_exit();
    
//交易结束
    
    
}