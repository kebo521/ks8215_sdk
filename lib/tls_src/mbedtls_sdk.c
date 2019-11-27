

#include "comm_type.h"
#define 	TRACE 	printf


#include "sm4.h"


#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#if defined(MBEDTLS_PLATFORM_C)
#include "mbedtls/platform.h"
#else
#include <stdio.h>
#include <stdlib.h>
#define mbedtls_time       time 
#define mbedtls_time_t     time_t
#define mbedtls_fprintf    fprintf
#define mbedtls_printf     printf
#endif
#include "mbedtls/md5.h"
#include "mbedtls/des.h"
#include "mbedtls/aes.h"

#include "mbedtls/md.h"
#include "mbedtls/pk.h"
#include "mbedtls/bignum.h"
#include "mbedtls/asn1.h"
#include "mbedtls/x509.h"
#include "mbedtls/x509_crl.h"
#include "mbedtls/x509_crt.h"
#include "mbedtls/sha1.h"
#include "mbedtls/sha256.h"

#include "mbedtls/base64.h"

#include "mbedtls/net_sockets.h"
#include "mbedtls/debug.h"
#include "mbedtls/ssl.h"
#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/error.h"
#include "mbedtls/certs.h"
#include "mbedtls/version.h"
#include "mbedtls/pem.h"


//#include <string.h>
#include "mbedtls/md_internal.h"

#include "mbedtls/pk_internal.h"

#include "mbedtls_sdk.h"

#include<time.h>


int api_md_hash(mbedtls_md_type_t hash_id,u8 *input, int ilen,u8 *output)
{
	mbedtls_md_info_t *md_info=(mbedtls_md_info_t *)mbedtls_md_info_from_type(hash_id);
	if(0 == mbedtls_md(md_info,input,ilen,output))
	{
		return mbedtls_md_get_size(md_info);
	}	
	return -1;
}

int api_md_hmac(mbedtls_md_type_t hash_id,u8 *key, int keylen,u8 *input, int ilen,u8 *output)
{
	mbedtls_md_info_t *md_info=(mbedtls_md_info_t *)mbedtls_md_info_from_type(hash_id);
	if(0 == mbedtls_md_hmac(md_info,key,keylen,input,ilen,output))
	{
		return mbedtls_md_get_size(md_info);
	}	
	return -1;
}

int api_md_starts(mbedtls_md_context_t *ctx,mbedtls_md_type_t hash_id)
{
	int ret;
	mbedtls_md_info_t *md_info=(mbedtls_md_info_t *)mbedtls_md_info_from_type(hash_id);
	mbedtls_md_init(ctx);
	if( ( ret = mbedtls_md_setup(ctx,md_info,0) ) != 0 )
	{
		TRACE("mbedtls_md_setup ERR[%d]\r\n", ret );
		return ret;
	}
	if( ( ret = mbedtls_md_starts(ctx ) ) != 0 )
    {
    	TRACE("mbedtls_md_starts ERR[%d]\r\n", ret );
        return ret;
    }
	return 0;
}

int api_md_update(mbedtls_md_context_t *ctx,unsigned char *input, size_t ilen)
{
	int ret;
	if( ( ret = mbedtls_md_update(ctx,input,ilen) ) != 0 )
    {
        TRACE("mbedtls_md_update ERR[%d]\r\n", ret );
        return ret;
    }
	return 0;
}	

    
int api_md_finish(mbedtls_md_context_t *ctx,unsigned char *output, size_t *Outlen)
{
	int ret;
	if( ( ret = mbedtls_md_finish(ctx,output) ) != 0 )
	{
		TRACE("mbedtls_md_update ERR[%d]\r\n", ret );
	}
	else
	{
		if(Outlen)
			*Outlen = mbedtls_md_get_size(ctx->md_info);
	}
	mbedtls_md_free(ctx);
	return ret;
}	
  

//==================================================================================

int f_GetRand(void *pInducer, unsigned char *pOutRand, size_t RandSize)
{
	int i;
	srand(*(unsigned int*)pInducer);
	for(i=0;i<RandSize;i++)
		pOutRand[i]=rand();
	return 0;
}

int api_pk_sign(mbedtls_pk_context *ctx,mbedtls_md_type_t hash_id,int padding,
                    unsigned char *pInData,size_t Inlen,
                    unsigned char *pOutsig,size_t *sig_len)
{
	int ret;
	u8	HashBuff[128]={0};
	time_t timer;//long	struct tm *tblock;	
	timer = time(NULL);
	
	TRACE("pk_pkcs1_sign[%d][%s]\r\n",ctx->pk_info->type,ctx->pk_info->name);
	if(ctx->pk_info->type == MBEDTLS_PK_RSA	\
		||ctx->pk_info->type == MBEDTLS_PK_RSA_ALT	\
		||ctx->pk_info->type == MBEDTLS_PK_RSASSA_PSS)
	{
		mbedtls_rsa_context * rsa = (mbedtls_rsa_context *) ctx->pk_ctx;
		rsa->padding = padding;
		rsa->hash_id = hash_id;
	}
	else if(ctx->pk_info->type == MBEDTLS_PK_SM2)
	{
		
	}
	if(pInData==NULL) return -6;
	if( ( ret = mbedtls_md(mbedtls_md_info_from_type(hash_id),pInData,Inlen,HashBuff) ) != 0 )
    {
        return( ret );
    }
	if(pOutsig==NULL) return -7;
	return mbedtls_pk_sign(ctx,hash_id,HashBuff,0,pOutsig,sig_len,&f_GetRand,&timer);
}


int api_pk_verify( mbedtls_pk_context *ctx, mbedtls_md_type_t hash_id,int padding,
               			unsigned char *pInData, size_t Inlen,
               			unsigned char *sig, size_t sig_len )
{
	
	int ret;
	u8	HashBuff[128]={0};
	if(ctx->pk_info->type == MBEDTLS_PK_RSA	\
		||ctx->pk_info->type == MBEDTLS_PK_RSA_ALT	\
		||ctx->pk_info->type == MBEDTLS_PK_RSASSA_PSS)
	{
		mbedtls_rsa_context * rsa = (mbedtls_rsa_context *) ctx->pk_ctx;
		rsa->padding = padding;
		rsa->hash_id = hash_id;
	}
	else if(ctx->pk_info->type == MBEDTLS_PK_SM2)
	{
		
	}
	if( ( ret = mbedtls_md(mbedtls_md_info_from_type(hash_id),pInData,Inlen,HashBuff) ) != 0 )
    {
        return( ret );
    }
	return mbedtls_pk_verify(ctx,hash_id,HashBuff,0,sig,sig_len);
}


int api_pk_decrypt( mbedtls_pk_context *ctx,
                unsigned char *input, size_t ilen,
                unsigned char *output, size_t *olen, size_t osize)
{
	time_t timer;//long	struct tm *tblock;	
	timer = time(NULL);
	return mbedtls_pk_decrypt(ctx,input,ilen,output,olen,osize,&f_GetRand,&timer);
}

int api_pk_encrypt( mbedtls_pk_context *ctx,
                unsigned char *input, size_t ilen,
                unsigned char *output, size_t *olen, size_t osize)
{
	time_t timer;//long	struct tm *tblock;	
	timer = time(NULL);
	return mbedtls_pk_encrypt(ctx,input,ilen,output,olen,osize,&f_GetRand,&timer);

}




int api_x509write_crt_der(mbedtls_x509write_cert *ctx, unsigned char *buf, size_t size)
{
	int ret;
	time_t timer;//long	struct tm *tblock;	
	timer = time(NULL);
	ret = mbedtls_x509write_crt_der(ctx,buf,size,&f_GetRand,&timer);
	if(ret > 0)
	{
		memmove(buf,buf+size-ret,ret);
	}
	return( ret );
}

//======================Âä†ÂØÜÈí•Êé•Âè£=========================================
int API_Crypt(int type, const u8* key, int keylen, const u8* iv, const u8* input, int inlen, u8* output, int * outlen, int mode)
{
	#if defined(MBEDTLS_DES_C)
	if(type==CRYPT_TYPE_DES)
	{
		if(keylen==8)
		{
			mbedtls_des_context ctx;
			int offset=0;
			mbedtls_des_init(&ctx );
			if(mode & CRYPT_MODE_DECRYPT)
				mbedtls_des_setkey_dec(&ctx,key);
			else
				mbedtls_des_setkey_enc(&ctx,key);
			if(mode&CRYPT_MODE_CBC)
			{
				int mbedMode;
				u8 mbediv[8];
				if(mode & CRYPT_MODE_DECRYPT)
					mbedMode=MBEDTLS_DES_DECRYPT;
				else
					mbedMode=MBEDTLS_DES_ENCRYPT;
				if(iv) memcpy(mbediv,iv,sizeof(mbediv));
				else memset(mbediv,0x00,sizeof(mbediv));
				mbedtls_des_crypt_cbc(&ctx,mbedMode,inlen,mbediv,input,output);
			}
			else 
			{
				for(offset=0;offset<inlen;offset+=8)
				{
					mbedtls_des_crypt_ecb(&ctx,input+offset,output+offset);
				}
			}
			mbedtls_des_free( &ctx );
			if(outlen) *outlen=inlen;
		}
		else 
		{	
			mbedtls_des3_context ctx3;
			int offset=0;
			if(keylen==16)
			{
				if(mode & CRYPT_MODE_DECRYPT)
					mbedtls_des3_set2key_dec(&ctx3,key);
				else
					mbedtls_des3_set2key_enc(&ctx3,key);
			}
			else
			{
				if(mode & CRYPT_MODE_DECRYPT)
					mbedtls_des3_set3key_dec(&ctx3,key);
				else
					mbedtls_des3_set3key_enc(&ctx3,key);
			}

			if(mode&CRYPT_MODE_CBC)
			{
				int mbedMode;
				u8 mbediv[8];
				if(mode & CRYPT_MODE_DECRYPT)
					mbedMode=MBEDTLS_DES_DECRYPT;
				else
					mbedMode=MBEDTLS_DES_ENCRYPT;
				if(iv) memcpy(mbediv,iv,sizeof(mbediv));
				else memset(mbediv,0x00,sizeof(mbediv));
				mbedtls_des3_crypt_cbc(&ctx3,mbedMode,inlen,mbediv,input,output);
			}
			else 
			{
				for(offset=0;offset<inlen;offset+=8)
				{
					mbedtls_des3_crypt_ecb(&ctx3,input+offset,output+offset);
				}
			}
			mbedtls_des3_free( &ctx3 );
			if(outlen) *outlen=inlen;
		}
	}
	else 
	#endif
	#if defined(MBEDTLS_AES_C)
	if(type==CRYPT_TYPE_AES)
	{
		int keybits,offset;
		mbedtls_aes_context ctx;
		mbedtls_aes_init(&ctx );
		keybits = keylen*8;//128;// + u * 64;
		if(mode & CRYPT_MODE_DECRYPT)
		{
		   offset=mbedtls_aes_setkey_dec(&ctx,key, keybits);
		   mode=MBEDTLS_AES_DECRYPT;
		}
		else
		{
			offset=mbedtls_aes_setkey_enc(&ctx,key, keybits );
			mode=MBEDTLS_AES_ENCRYPT;
		}
		if(offset<0)
		{
			TRACE("mbedtls_aes_setkey ret[%d]Err\r\n",offset);
			return offset;
		}
		
		for(offset=0;offset<inlen;offset+=16)
		{
			mbedtls_aes_crypt_ecb(&ctx,mode,input+offset,output+offset);
		}
		mbedtls_aes_free( &ctx ); 
	}
	else 
	#endif
	if(type==CRYPT_TYPE_SM4)
	{
		if(mode & CRYPT_MODE_DECRYPT)
			inlen=API_SM4_DEC((u8*)input,inlen,output,(u8*)key);
		else
			inlen=API_SM4_ENC((u8*)input,inlen,output,(u8*)key);
		if(outlen) *outlen=inlen;
	}
	else 
	{
		return -5;
	}
	return 0;
}



int APP_rsa_PrivatekeyPublic(char *pKey,int keyLen,unsigned char *pInData,unsigned char* pOutData)
{
	int ret;
	mbedtls_pk_context ctxPk;
	mbedtls_pk_init(&ctxPk);
	ret=mbedtls_pk_parse_key(&ctxPk,(u8*)pKey,keyLen,NULL,0);
	if(0 == ret)
	{
		ret=mbedtls_rsa_public((mbedtls_rsa_context *)ctxPk.pk_ctx,pInData,pOutData);
	}
	mbedtls_pk_free(&ctxPk);
	return ret;
}

int APP_rsa_PublickeyPublic(char *pKey,int keyLen,unsigned char *pInData,unsigned char* pOutData)
{
	int ret;
	mbedtls_pk_context ctxPk;
	mbedtls_pk_init(&ctxPk);
	ret=mbedtls_pk_parse_public_key(&ctxPk,(u8*)pKey,keyLen);
	if(0 == ret)
	{
		ret=mbedtls_rsa_public((mbedtls_rsa_context *)ctxPk.pk_ctx,pInData,pOutData);
	}
	mbedtls_pk_free(&ctxPk);
	return ret;
}

//---------------------------------------------------------
const API_HASH_Def tls_hash_funtion={
	{'s','h','a',5},	
	api_md_hash,
	api_md_hmac,
	api_md_starts,
	api_md_update,
	api_md_finish,
};

const API_RSA_Def tls_rsa_funtion={
	{'r','s','a',6},	
	mbedtls_rsa_init,
	mbedtls_rsa_import_raw,
	mbedtls_rsa_public,
	mbedtls_rsa_private,
	APP_rsa_PrivatekeyPublic,
	APP_rsa_PublickeyPublic,
};

//=====================PK∂‘Õ‚Ω”ø⁄================================================
const API_PK_Def pk_inter={
	{'P','K','\0',8},
	mbedtls_pk_init,
	mbedtls_pk_free,
	api_pk_decrypt,
	api_pk_encrypt,
	api_pk_sign,
	api_pk_verify,
	mbedtls_pk_parse_key,
	mbedtls_pk_parse_public_key,
};


//========================================================================
const API_CRT_Def crt_inter={
	{'5','0','9',7},
	NULL,
	mbedtls_x509_crt_init,
	mbedtls_x509_crt_parse,
	mbedtls_x509_crt_free,	//init->parse->free
	mbedtls_x509_crt_verify,
	api_x509write_crt_der,
	mbedtls_pem_write_buffer,
};


//----------------------------------------------------------
const API_Crypt_Def api_crypt={
	{'c','r','y',3},	
	API_Crypt,
	mbedtls_base64_encode,
	mbedtls_base64_decode,
};

//-----------------------------------------------------------
const API_TLS_INTERFACE api_tls_InterFace={
		{'t','l','s',6},
		MBEDTLS_VERSION_STRING_FULL,
		&tls_hash_funtion,
		&tls_rsa_funtion,
		&pk_inter,
		&crt_inter,
		&api_crypt,
};





