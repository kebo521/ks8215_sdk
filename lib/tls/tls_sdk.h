#ifndef _TLS_SDK_
#define _TLS_SDK_

#include "md.h"
#include "pk.h"
#include "bignum.h"
#include "asn1.h"
#include "rsa.h"
#include "x509.h"
#include "x509_crl.h"
#include "x509_crt.h"
//===========================================================================================================

extern int api_md_hash(mbedtls_md_type_t hash_id,u8 *input, int ilen,u8 *output);
extern int api_md_hmac(mbedtls_md_type_t hash_id,u8 *key, int keylen,u8 *input, int ilen,u8 *output);
extern int api_md_starts(mbedtls_md_context_t *ctx,mbedtls_md_type_t hash_id);
extern int api_md_update(mbedtls_md_context_t *ctx,unsigned char *input, size_t ilen);
extern int api_md_finish(mbedtls_md_context_t *ctx,unsigned char *output, size_t *Outlen);

extern int APP_rsa_PrivatekeyPublic(char *pKey,int keyLen,unsigned char *pInData,unsigned char* pOutData);
extern int APP_rsa_PublickeyPublic(char *pKey,int keyLen,unsigned char *pInData,unsigned char* pOutData);

//extern int f_GetRand(void *pInducer, unsigned char *pOutRand, size_t RandSize);
extern int api_pk_sign(mbedtls_pk_context *ctx,mbedtls_md_type_t hash_id,int padding,unsigned char *pInData,size_t Inlen,unsigned char *pOutsig,size_t *sig_len);
extern int api_pk_verify( mbedtls_pk_context *ctx, mbedtls_md_type_t hash_id,int padding,unsigned char *pInData, size_t Inlen,unsigned char *sig, size_t sig_len );
extern int api_pk_decrypt( mbedtls_pk_context *ctx,unsigned char *input, size_t ilen,unsigned char *output, size_t *olen, size_t osize);
extern int api_pk_encrypt( mbedtls_pk_context *ctx,unsigned char *input, size_t ilen,unsigned char *output, size_t *olen, size_t osize);
extern int api_x509write_crt_der(mbedtls_x509write_cert *ctx, unsigned char *buf, size_t size);



//===========================================================================================================
//----------------------------------------------------------------------------------------------------------------------
//@加解密计算

	/**
     * 加密算法类型
     */
    enum CRYPT_TYPE 
    {
        CRYPT_TYPE_DES      = 1,	//!< DES算法
        CRYPT_TYPE_SM4      = 2,	//!< SM4算法
        CRYPT_TYPE_AES      = 3,	//!< AES算法
        CRYPT_TYPE_RSA      = 11,	//!< RSA算法
        CRYPT_TYPE_SM2      = 12,	//!< SM2算法
    };

    /**
     * 加密算法模式
     */
    enum CRYPT_MODE 
    {
        /* 加密解密 */
        CRYPT_MODE_ENCRYPT     = 0x00,		//!< 公钥加密
        CRYPT_MODE_DECRYPT     = 0x01,		//!< 私钥解密

        /* 工作模式 */
        CRYPT_MODE_ECB         = 0x0000,	//!< DES ECB
        CRYPT_MODE_CBC         = 0x0100,	//!< DES CBC
        CRYPT_MODE_OFB         = 0x0200,	//!< DES OFB
        CRYPT_MODE_CFB         = 0x0400,	//!< DES CFB
    
    };
    
	
extern int API_Crypt(int type, const u8* key, int keylen, const u8* iv, const u8* input, int inlen, u8* output, int * outlen, int mode);
//---------------------------------------------------------


typedef struct  
{
	char 	Mask[4]; 			// "HASH"
	int		(*md)(mbedtls_md_type_t,u8 *,int,u8 *);
	int		(*md_hmac)(mbedtls_md_type_t,u8 *, int,u8 *,int,u8 *);
	int (*md_starts)(mbedtls_md_context_t *,mbedtls_md_type_t);
	int (*md_update)(mbedtls_md_context_t *,unsigned char *, size_t );
	int (*md_finish)(mbedtls_md_context_t *,unsigned char *, size_t *);
}API_HASH_Def;

typedef struct  
{
	char Mask[4]; 			// "RSA"
	void (*init)(mbedtls_rsa_context *,int ,int );	//(mbedtls_rsa_context *ctx,int padding,int hash_id)
	int (*import_raw)(mbedtls_rsa_context *ctx,						/*mbedtls_rsa_context *ctx,*/
                            unsigned char const *N, size_t N_len,		/*unsigned char const *N, size_t N_len,*/
                            unsigned char const *P, size_t P_len,		/*unsigned char const *P, size_t P_len,*/
                            unsigned char const *Q, size_t Q_len,		/*unsigned char const *Q, size_t Q_len,*/
                            unsigned char const *D, size_t D_len,		/*unsigned char const *D, size_t D_len,*/
                            unsigned char const *E, size_t E_len);		/*unsigned char const *E, size_t E_len,*/
	int (*public)( mbedtls_rsa_context *ctx,const unsigned char *input,unsigned char *output);
	int (*private)( mbedtls_rsa_context *ctx,
                 int (*f_rng)(void *, unsigned char *, size_t), void *p_rng,
                 const unsigned char *input,unsigned char *output );

	int (*PriKey_Public)(char *,int ,unsigned char*,unsigned char*);	//(char *pPriKey,int keyLen,u8 *pInData,u8* pOutData)
	int (*PubKey_Public)(char *,int ,unsigned char*,unsigned char*);	//(char *pPubKey,int keyLen,u8 *pInData,u8* pOutData)
}API_RSA_Def;


typedef struct  
{
	char 	Mask[4]; 	// "PK"
	void    (*pk_init)(mbedtls_pk_context *);
	void 	(*pk_free)(mbedtls_pk_context *);
	int 	(*pk_decrypt)( mbedtls_pk_context *,unsigned char *,size_t,unsigned char *,size_t *,size_t);
	int 	(*pk_encrypt)( mbedtls_pk_context *,unsigned char *,size_t,unsigned char *,size_t *,size_t);
	int 	(*pk_sign)(mbedtls_pk_context *,mbedtls_md_type_t,int,unsigned char *,size_t,unsigned char *,size_t *);
	int 	(*pk_verify)(mbedtls_pk_context *,mbedtls_md_type_t,int,unsigned char *,size_t,unsigned char *, size_t);
	int 	(*pk_parse_key)(mbedtls_pk_context *,const unsigned char *,size_t ,const unsigned char *,size_t);
	int 	(*pk_parse_public_key)( mbedtls_pk_context *,const unsigned char *, size_t);
}API_PK_Def;

typedef struct  
{
	char 	Mask[4]; 	// "CRT"
	int 	(*x509_self_test)( int verbose );
	void 	(*x509_crt_init)( mbedtls_x509_crt *crt );
	int 	(*x509_crt_parse)( mbedtls_x509_crt *chain, const unsigned char *buf, size_t buflen );
	void 	(*x509_crt_free)( mbedtls_x509_crt *crt );
	int 	(*x509_crt_verify)( mbedtls_x509_crt *crt,
                     mbedtls_x509_crt *trust_ca,
                     mbedtls_x509_crl *ca_crl,
                     const char *cn, uint32_t *flags,
                     int (*f_vrfy)(void *, mbedtls_x509_crt *, int, uint32_t *),
                     void *p_vrfy );

	int (*x509write_crt_der)(mbedtls_x509write_cert *, unsigned char *, size_t);
	int (*pem_write_buffer)(const char*, const char*,const unsigned char *, size_t,unsigned char *,size_t ,size_t *);
}API_CRT_Def;


typedef struct  
{
	char 	Mask[4]; 	// "crypt"
	int 	(*Crypt)(int, const u8*,int,const u8*,const u8*,int,u8*,int *,int);
	
	int 	(*base64_encode)(unsigned char*,size_t,size_t *,const unsigned char *,size_t);
	int 	(*base64_decode)(unsigned char*,size_t,size_t *,const unsigned char *,size_t);
}API_Crypt_Def;




typedef struct 
{
	char 						Mask[4]; 				// "Tls"
	const char*					pTlsVerSion; 	//tls 库版本号
	const API_HASH_Def*  		hash;  		// 摘要运算
	const API_RSA_Def*			rsa;		// rsa 运算
	const API_PK_Def*			pk;			// PKcs处理功能接口
	const API_CRT_Def*			crt;		// 证书处理
	const API_Crypt_Def*		cry;		//加密钥接口
}API_TLS_INTERFACE;
//-----------------------------------------------------------
extern const API_TLS_INTERFACE api_tls_InterFace;
	

//extern void* tls_InterfaceEntry(void);




#endif
