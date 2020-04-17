

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


#if defined(MBEDTLS_DEBUG_C)
static void my_stdout(const char *str )
{
	mbedtls_printf("%s",str);
}


static void my_debug( void *ctx, int level,
                      const char *file, int line,
                      const char *str )
{
	mbedtls_printf("%s:%04d: %s", file, line, str );
}
#endif

typedef struct
{
	mbedtls_net_context server_fd;
	mbedtls_entropy_context entropy;
	mbedtls_ctr_drbg_context ctr_drbg;
    mbedtls_ssl_context ssl;
    mbedtls_ssl_config conf;
    mbedtls_x509_crt cacert;
	mbedtls_ssl_session saved_session;
	int read_timeout;
	u8 sessionFirst,FlowState;
	//unsigned char RecvBuff[4096];
}mbedtls_net_data;

static mbedtls_net_data mbedtlsNetData;
//"ssl_client1"

int APP_SSL_Open(mbedtls_ssl_send_t *f_send,mbedtls_ssl_recv_timeout_t *f_recv_timeout,int timeoutMs,
							unsigned char *crtbuf, int crtlen)
{
	int ret;
	mbedtlsNetData.read_timeout   = timeoutMs;
	mbedtlsNetData.sessionFirst   = 0;
	mbedtlsNetData.FlowState		=0;
	mbedtls_ssl_config_init( &mbedtlsNetData.conf );
	#if defined(MBEDTLS_DEBUG_C)
	mbedtls_debug_set_threshold( 1 );
	mbedtls_ssl_conf_dbg( &mbedtlsNetData.conf, my_debug, my_stdout );
	#endif
	//mbedtls_net_init( &mbedtlsNetData.server_fd );
	mbedtls_ssl_init( &mbedtlsNetData.ssl);
	mbedtls_x509_crt_init( &mbedtlsNetData.cacert );
	mbedtls_ctr_drbg_init( &mbedtlsNetData.ctr_drbg );
	mbedtls_entropy_init(&mbedtlsNetData.entropy );
	mbedtls_ssl_session_init(&mbedtlsNetData.saved_session);
	mbedtlsNetData.FlowState=1;

	if( ( ret = mbedtls_ctr_drbg_seed( &mbedtlsNetData.ctr_drbg, mbedtls_entropy_func, &mbedtlsNetData.entropy,
									   (const unsigned char *)"ssl_client1",1) ) != 0 )
	{
		mbedtls_printf( " failed\n	! mbedtls_ctr_drbg_seed returned %d\n", ret );
		return -1;
	}
	mbedtlsNetData.FlowState=2;
	/*
	 * 0. Initialize certificates
	 */
	if(crtbuf==NULL)
	{
		crtbuf=(unsigned char*)mbedtls_test_cas_pem;
		crtlen=mbedtls_test_cas_pem_len;
	}
	ret = mbedtls_x509_crt_parse(&mbedtlsNetData.cacert,crtbuf,crtlen);
	if( ret < 0 )
	{
		mbedtls_printf( " failed\n	!  mbedtls_x509_crt_parse returned -0x%x\n\n", -ret );
		return -2;
	}
	mbedtlsNetData.FlowState=3;
	/*
	 * 2. Setup stuff
	 */
	if( ( ret = mbedtls_ssl_config_defaults( &mbedtlsNetData.conf,
					MBEDTLS_SSL_IS_CLIENT,
					MBEDTLS_SSL_TRANSPORT_STREAM,
					MBEDTLS_SSL_PRESET_DEFAULT ) ) != 0 )
	{
		mbedtls_printf( " failed\n	! mbedtls_ssl_config_defaults returned %d\n\n", ret );
		return -3;
	}
	mbedtlsNetData.FlowState=4;
	/* OPTIONAL is not optimal for security,
	 * but makes interop easier in this simplified example */
	mbedtls_ssl_conf_authmode( &mbedtlsNetData.conf, MBEDTLS_SSL_VERIFY_OPTIONAL );
	mbedtls_ssl_conf_ca_chain( &mbedtlsNetData.conf, &mbedtlsNetData.cacert, NULL );
	mbedtls_ssl_conf_rng( &mbedtlsNetData.conf, mbedtls_ctr_drbg_random, &mbedtlsNetData.ctr_drbg );
	//mbedtls_ssl_conf_dbg( &conf, my_debug, stdout );
	if( ( ret = mbedtls_ssl_setup(&mbedtlsNetData.ssl, &mbedtlsNetData.conf ) ) != 0 )
	{
		mbedtls_printf( " failed\n	! mbedtls_ssl_setup returned %d\n\n", ret );
		return -4;
	}
	mbedtlsNetData.FlowState=5;

	if( ( ret = mbedtls_ssl_set_hostname(&mbedtlsNetData.ssl, NULL) ) != 0 )
	{
		mbedtls_printf( " failed\n	! mbedtls_ssl_set_hostname returned %d\n\n", ret );
		return -5;
	}
	mbedtls_ssl_set_bio(&mbedtlsNetData.ssl, &mbedtlsNetData.server_fd,f_send,NULL,f_recv_timeout);
	mbedtlsNetData.server_fd.fd=0;
	mbedtlsNetData.FlowState=6;
	return 0;
}


int APP_SSL_Handshake(void)
{
	int ret;
	uint32_t flags;
	mbedtlsNetData.FlowState=10;
	mbedtlsNetData.server_fd.fd=1;
	if(mbedtlsNetData.sessionFirst)
	{
		if( ( ret = mbedtls_ssl_session_reset( &mbedtlsNetData.ssl ) ) != 0 )
		{
			mbedtls_printf( " failed\n	! mbedtls_ssl_session_reset returned -0x%x\n\n",-ret );
			return -1;
		}
		if(( ret = mbedtls_ssl_set_session( &mbedtlsNetData.ssl, &mbedtlsNetData.saved_session) ) != 0 )
		{
			mbedtls_printf( " failed\n	! mbedtls_ssl_conf_session returned %d\n\n",ret );
			return -1;
		}
	}
	mbedtls_ssl_conf_read_timeout(&mbedtlsNetData.conf,mbedtlsNetData.read_timeout);
	mbedtlsNetData.FlowState=11;
	/*
	 * 4. Handshake
	 */
	while( ( ret = mbedtls_ssl_handshake( &mbedtlsNetData.ssl ) ) != 0 )
	{
		if( ret != MBEDTLS_ERR_SSL_WANT_READ && ret != MBEDTLS_ERR_SSL_WANT_WRITE )
		{
			mbedtls_printf( "\n failed->  ! mbedtls_ssl_handshake returned -0x%x\n\n", -ret );
			return -2;
		}
	}
	mbedtlsNetData.FlowState=12;

	if( ( ret = mbedtls_ssl_get_session( &mbedtlsNetData.ssl, &mbedtlsNetData.saved_session ) ) != 0 )
	{
		mbedtls_printf( " failed\n	! mbedtls_ssl_get_session returned -0x%x\n\n",-ret );
		return -3;
	}
	mbedtlsNetData.sessionFirst=1;
	mbedtlsNetData.FlowState=13;
	/*
	 * 5. Verify the server certificate
	 */
	/* In real life, we probably want to bail out when ret != 0 */
	if( ( flags = mbedtls_ssl_get_verify_result(&mbedtlsNetData.ssl) ) != 0 )
	{
		char vrfy_buf[512];
		mbedtls_printf( "\n Verifying peer X.509 certificate...failed " );
		mbedtls_x509_crt_verify_info( vrfy_buf, sizeof( vrfy_buf ), "  ! ", flags );
		mbedtls_printf( "%s\n", vrfy_buf );
	}
	mbedtlsNetData.server_fd.fd=2;
	mbedtlsNetData.FlowState=14;
	return 0;
}

int APP_SSL_Send(unsigned char *buf, int len)
{
	int ret;
	if(mbedtlsNetData.server_fd.fd < 2)
	{
		mbedtls_printf( "APP_SSL_NetSend State error %d\n\n", mbedtlsNetData.server_fd.fd);
		return -1;
	}
	mbedtlsNetData.FlowState=20;
	mbedtls_ssl_conf_read_timeout(&mbedtlsNetData.conf,mbedtlsNetData.read_timeout);
	while( ( ret = mbedtls_ssl_write( &mbedtlsNetData.ssl, buf, len ) ) <= 0 )
    {
        if( ret != MBEDTLS_ERR_SSL_WANT_READ && ret != MBEDTLS_ERR_SSL_WANT_WRITE )
        {
            mbedtls_printf( " failed\n  ! mbedtls_ssl_write returned %d\n\n", ret );
            return ret;
        }
    }
	mbedtlsNetData.server_fd.fd =3;
	mbedtlsNetData.FlowState=21;
	return ret;
}

int APP_SSL_Recv(unsigned char *buf, int BuffSize)
{
	int ret;
	if(mbedtlsNetData.server_fd.fd < 2)
	{
		mbedtls_printf( "APP SSL NetRecv State error %d\n\n", mbedtlsNetData.server_fd.fd);
		return -1;
	}
	mbedtlsNetData.FlowState=30;
	mbedtls_ssl_conf_read_timeout(&mbedtlsNetData.conf,mbedtlsNetData.read_timeout);
	do
    {
		ret = mbedtls_ssl_read( &mbedtlsNetData.ssl, buf, BuffSize);
		if( ret == MBEDTLS_ERR_SSL_WANT_READ || ret == MBEDTLS_ERR_SSL_WANT_WRITE )
		{
			mbedtls_printf( "mbedtls ssl read continue %d\n\n", ret );
			continue;
		}
		if( ret == MBEDTLS_ERR_SSL_PEER_CLOSE_NOTIFY )
		{
			mbedtls_ssl_close_notify(&mbedtlsNetData.ssl );
			mbedtlsNetData.server_fd.fd = 0;
			return MBEDTLS_ERR_SSL_PEER_CLOSE_NOTIFY;
		}
		if( ret < 0 )
		{
			mbedtls_printf( "failed\n  ! mbedtls ssl readbuf ret -0x%x\n\n", -ret );
		}
		else if( ret == 0 )
		{
			mbedtls_printf( "\n\nEOF\n\n" );
			return 0;
		}
		mbedtlsNetData.server_fd.fd =4;
		mbedtlsNetData.FlowState=31;
		return ret;
    }
    while( 1 );
}

int APP_SSL_GetState(int TimeOutMs)
{
	int ret;
	unsigned char *pRecvBuff;
	if(mbedtlsNetData.server_fd.fd < 2)
	{
		mbedtls_printf( "APP SSL NetRecv State error %d\n\n", mbedtlsNetData.server_fd.fd);
		return -1;
	}
	mbedtls_ssl_conf_read_timeout(&mbedtlsNetData.conf,TimeOutMs);
	pRecvBuff=(unsigned char*)malloc(4096);
	while(1)
	{
		ret = mbedtls_ssl_read(&mbedtlsNetData.ssl, pRecvBuff, 4096);
		if( ret == MBEDTLS_ERR_SSL_WANT_READ || ret == MBEDTLS_ERR_SSL_WANT_WRITE )
		{
			mbedtls_printf( "mbedtls ssl read continue -0x%x\n\n", -ret );
			continue;
		}
		if(ret == MBEDTLS_ERR_SSL_PEER_CLOSE_NOTIFY)
		{
			mbedtls_ssl_close_notify( &mbedtlsNetData.ssl );
			mbedtlsNetData.server_fd.fd = 0;
			ret = MBEDTLS_ERR_SSL_PEER_CLOSE_NOTIFY;
			break;
			//return MBEDTLS_ERR_SSL_PEER_CLOSE_NOTIFY;
		}
		if( ret == 0 )
		{
			mbedtls_printf( "\n\nGetState EOF\n\n" );
			ret = 1;
			break;
		}
		mbedtls_printf( "ssl read State ret -0x%x\n\n", -ret );
		break;
	}
	free(pRecvBuff);
	return ret;
}

void APP_SSL_Close(void)
{
    //mbedtls_net_free( &mbedtlsNetData.server_fd );
    if(mbedtlsNetData.FlowState>0)
    {
		mbedtls_x509_crt_free( &mbedtlsNetData.cacert );
		mbedtls_ssl_free( &mbedtlsNetData.ssl );
		mbedtls_ssl_config_free( &mbedtlsNetData.conf );
		mbedtls_ctr_drbg_free( &mbedtlsNetData.ctr_drbg );
		mbedtls_entropy_free(&mbedtlsNetData.entropy );
		mbedtls_ssl_session_free(&mbedtlsNetData.saved_session);
		mbedtlsNetData.sessionFirst=0;
		mbedtlsNetData.server_fd.fd = -1;
	}
}

const API_SSL_Def ssl_net_funtion={
	"SSL",
	APP_SSL_Open,
	APP_SSL_Handshake,
	APP_SSL_Send,
	APP_SSL_Recv,
	APP_SSL_GetState,
	APP_SSL_Close,
};

//===================================================================================

//-----------------------------------------------------------
const API_TLS_INTERFACE api_tls_InterFace={
		{'t','l','s',7},
		MBEDTLS_VERSION_STRING_FULL,
		&tls_hash_funtion,
		&tls_rsa_funtion,
		&pk_inter,
		&crt_inter,
		&api_crypt,
		&ssl_net_funtion,
};





