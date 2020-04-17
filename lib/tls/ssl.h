/**
 * \file ssl.h
 *
 * \brief SSL/TLS functions.
 */
#ifndef MBEDTLS_SSL_H
#define MBEDTLS_SSL_H


#define MBEDTLS_ERR_NET_SOCKET_FAILED                     -0x0042  /**< Failed to open a socket. */
#define MBEDTLS_ERR_NET_CONNECT_FAILED                    -0x0044  /**< The connection to the given server / port failed. */
#define MBEDTLS_ERR_NET_BIND_FAILED                       -0x0046  /**< Binding of the socket failed. */
#define MBEDTLS_ERR_NET_LISTEN_FAILED                     -0x0048  /**< Could not listen on the socket. */
#define MBEDTLS_ERR_NET_ACCEPT_FAILED                     -0x004A  /**< Could not accept the incoming connection. */
#define MBEDTLS_ERR_NET_RECV_FAILED                       -0x004C  /**< Reading information from the socket failed. */
#define MBEDTLS_ERR_NET_SEND_FAILED                       -0x004E  /**< Sending information through the socket failed. */
#define MBEDTLS_ERR_NET_CONN_RESET                        -0x0050  /**< Connection was reset by peer. */
#define MBEDTLS_ERR_NET_UNKNOWN_HOST                      -0x0052  /**< Failed to get an IP address for the given hostname. */
#define MBEDTLS_ERR_NET_BUFFER_TOO_SMALL                  -0x0043  /**< Buffer is too small to hold the data. */
#define MBEDTLS_ERR_NET_INVALID_CONTEXT                   -0x0045  /**< The context is invalid, eg because it was free()ed. */
#define MBEDTLS_ERR_NET_POLL_FAILED                       -0x0047  /**< Polling the net context failed. */
#define MBEDTLS_ERR_NET_BAD_INPUT_DATA                    -0x0049  /**< Input invalid. */

//#include "ssl_ciphersuites.h"

/*
 * SSL Error codes
 */
#define MBEDTLS_ERR_SSL_FEATURE_UNAVAILABLE               -0x7080  /**< The requested feature is not available. */
#define MBEDTLS_ERR_SSL_BAD_INPUT_DATA                    -0x7100  /**< Bad input parameters to function. */
#define MBEDTLS_ERR_SSL_INVALID_MAC                       -0x7180  /**< Verification of the message MAC failed. */
#define MBEDTLS_ERR_SSL_INVALID_RECORD                    -0x7200  /**< An invalid SSL record was received. */
#define MBEDTLS_ERR_SSL_CONN_EOF                          -0x7280  /**< The connection indicated an EOF. */
#define MBEDTLS_ERR_SSL_UNKNOWN_CIPHER                    -0x7300  /**< An unknown cipher was received. */
#define MBEDTLS_ERR_SSL_NO_CIPHER_CHOSEN                  -0x7380  /**< The server has no ciphersuites in common with the client. */
#define MBEDTLS_ERR_SSL_NO_RNG                            -0x7400  /**< No RNG was provided to the SSL module. */
#define MBEDTLS_ERR_SSL_NO_CLIENT_CERTIFICATE             -0x7480  /**< No client certification received from the client, but required by the authentication mode. */
#define MBEDTLS_ERR_SSL_CERTIFICATE_TOO_LARGE             -0x7500  /**< Our own certificate(s) is/are too large to send in an SSL message. */
#define MBEDTLS_ERR_SSL_CERTIFICATE_REQUIRED              -0x7580  /**< The own certificate is not set, but needed by the server. */
#define MBEDTLS_ERR_SSL_PRIVATE_KEY_REQUIRED              -0x7600  /**< The own private key or pre-shared key is not set, but needed. */
#define MBEDTLS_ERR_SSL_CA_CHAIN_REQUIRED                 -0x7680  /**< No CA Chain is set, but required to operate. */
#define MBEDTLS_ERR_SSL_UNEXPECTED_MESSAGE                -0x7700  /**< An unexpected message was received from our peer. */
#define MBEDTLS_ERR_SSL_FATAL_ALERT_MESSAGE               -0x7780  /**< A fatal alert message was received from our peer. */
#define MBEDTLS_ERR_SSL_PEER_VERIFY_FAILED                -0x7800  /**< Verification of our peer failed. */
#define MBEDTLS_ERR_SSL_PEER_CLOSE_NOTIFY                 -0x7880  /**< The peer notified us that the connection is going to be closed. */
#define MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO               -0x7900  /**< Processing of the ClientHello handshake message failed. */
#define MBEDTLS_ERR_SSL_BAD_HS_SERVER_HELLO               -0x7980  /**< Processing of the ServerHello handshake message failed. */
#define MBEDTLS_ERR_SSL_BAD_HS_CERTIFICATE                -0x7A00  /**< Processing of the Certificate handshake message failed. */
#define MBEDTLS_ERR_SSL_BAD_HS_CERTIFICATE_REQUEST        -0x7A80  /**< Processing of the CertificateRequest handshake message failed. */
#define MBEDTLS_ERR_SSL_BAD_HS_SERVER_KEY_EXCHANGE        -0x7B00  /**< Processing of the ServerKeyExchange handshake message failed. */
#define MBEDTLS_ERR_SSL_BAD_HS_SERVER_HELLO_DONE          -0x7B80  /**< Processing of the ServerHelloDone handshake message failed. */
#define MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE        -0x7C00  /**< Processing of the ClientKeyExchange handshake message failed. */
#define MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE_RP     -0x7C80  /**< Processing of the ClientKeyExchange handshake message failed in DHM / ECDH Read Public. */
#define MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE_CS     -0x7D00  /**< Processing of the ClientKeyExchange handshake message failed in DHM / ECDH Calculate Secret. */
#define MBEDTLS_ERR_SSL_BAD_HS_CERTIFICATE_VERIFY         -0x7D80  /**< Processing of the CertificateVerify handshake message failed. */
#define MBEDTLS_ERR_SSL_BAD_HS_CHANGE_CIPHER_SPEC         -0x7E00  /**< Processing of the ChangeCipherSpec handshake message failed. */
#define MBEDTLS_ERR_SSL_BAD_HS_FINISHED                   -0x7E80  /**< Processing of the Finished handshake message failed. */
#define MBEDTLS_ERR_SSL_ALLOC_FAILED                      -0x7F00  /**< Memory allocation failed */
#define MBEDTLS_ERR_SSL_HW_ACCEL_FAILED                   -0x7F80  /**< Hardware acceleration function returned with error */
#define MBEDTLS_ERR_SSL_HW_ACCEL_FALLTHROUGH              -0x6F80  /**< Hardware acceleration function skipped / left alone data */
#define MBEDTLS_ERR_SSL_COMPRESSION_FAILED                -0x6F00  /**< Processing of the compression / decompression failed */
#define MBEDTLS_ERR_SSL_BAD_HS_PROTOCOL_VERSION           -0x6E80  /**< Handshake protocol not within min/max boundaries */
#define MBEDTLS_ERR_SSL_BAD_HS_NEW_SESSION_TICKET         -0x6E00  /**< Processing of the NewSessionTicket handshake message failed. */
#define MBEDTLS_ERR_SSL_SESSION_TICKET_EXPIRED            -0x6D80  /**< Session ticket has expired. */
#define MBEDTLS_ERR_SSL_PK_TYPE_MISMATCH                  -0x6D00  /**< Public key type mismatch (eg, asked for RSA key exchange and presented EC key) */
#define MBEDTLS_ERR_SSL_UNKNOWN_IDENTITY                  -0x6C80  /**< Unknown identity received (eg, PSK identity) */
#define MBEDTLS_ERR_SSL_INTERNAL_ERROR                    -0x6C00  /**< Internal error (eg, unexpected failure in lower-level module) */
#define MBEDTLS_ERR_SSL_COUNTER_WRAPPING                  -0x6B80  /**< A counter would wrap (eg, too many messages exchanged). */
#define MBEDTLS_ERR_SSL_WAITING_SERVER_HELLO_RENEGO       -0x6B00  /**< Unexpected message at ServerHello in renegotiation. */
#define MBEDTLS_ERR_SSL_HELLO_VERIFY_REQUIRED             -0x6A80  /**< DTLS client must retry for hello verification */
#define MBEDTLS_ERR_SSL_BUFFER_TOO_SMALL                  -0x6A00  /**< A buffer is too small to receive or write a message */
#define MBEDTLS_ERR_SSL_NO_USABLE_CIPHERSUITE             -0x6980  /**< None of the common ciphersuites is usable (eg, no suitable certificate, see debug messages). */
#define MBEDTLS_ERR_SSL_WANT_READ                         -0x6900  /**< No data of requested type currently available on underlying transport. */
#define MBEDTLS_ERR_SSL_WANT_WRITE                        -0x6880  /**< Connection requires a write call. */
#define MBEDTLS_ERR_SSL_TIMEOUT                           -0x6800  /**< The operation timed out. */
#define MBEDTLS_ERR_SSL_CLIENT_RECONNECT                  -0x6780  /**< The client initiated a reconnect from the same port. */
#define MBEDTLS_ERR_SSL_UNEXPECTED_RECORD                 -0x6700  /**< Record header looks valid but is not expected. */
#define MBEDTLS_ERR_SSL_NON_FATAL                         -0x6680  /**< The alert message received indicates a non-fatal error. */
#define MBEDTLS_ERR_SSL_INVALID_VERIFY_HASH               -0x6600  /**< Couldn't set the hash for verifying CertificateVerify */
#define MBEDTLS_ERR_SSL_CONTINUE_PROCESSING               -0x6580  /**< Internal-only message signaling that further message-processing should be done */

/*
 * Various constants
 */
#define MBEDTLS_SSL_MAJOR_VERSION_3             3
#define MBEDTLS_SSL_MINOR_VERSION_0             0   /*!< SSL v3.0 */
#define MBEDTLS_SSL_MINOR_VERSION_1             1   /*!< TLS v1.0 */
#define MBEDTLS_SSL_MINOR_VERSION_2             2   /*!< TLS v1.1 */
#define MBEDTLS_SSL_MINOR_VERSION_3             3   /*!< TLS v1.2 */

#define MBEDTLS_SSL_TRANSPORT_STREAM            0   /*!< TLS      */
#define MBEDTLS_SSL_TRANSPORT_DATAGRAM          1   /*!< DTLS     */

#define MBEDTLS_SSL_MAX_HOST_NAME_LEN           255 /*!< Maximum host name defined in RFC 1035 */

/* RFC 6066 section 4, see also mfl_code_to_length in ssl_tls.c
 * NONE must be zero so that memset()ing structure to zero works */
#define MBEDTLS_SSL_MAX_FRAG_LEN_NONE           0   /*!< don't use this extension   */
#define MBEDTLS_SSL_MAX_FRAG_LEN_512            1   /*!< MaxFragmentLength 2^9      */
#define MBEDTLS_SSL_MAX_FRAG_LEN_1024           2   /*!< MaxFragmentLength 2^10     */
#define MBEDTLS_SSL_MAX_FRAG_LEN_2048           3   /*!< MaxFragmentLength 2^11     */
#define MBEDTLS_SSL_MAX_FRAG_LEN_4096           4   /*!< MaxFragmentLength 2^12     */
#define MBEDTLS_SSL_MAX_FRAG_LEN_INVALID        5   /*!< first invalid value        */

#define MBEDTLS_SSL_IS_CLIENT                   0
#define MBEDTLS_SSL_IS_SERVER                   1

#define MBEDTLS_SSL_IS_NOT_FALLBACK             0
#define MBEDTLS_SSL_IS_FALLBACK                 1

#define MBEDTLS_SSL_EXTENDED_MS_DISABLED        0
#define MBEDTLS_SSL_EXTENDED_MS_ENABLED         1

#define MBEDTLS_SSL_ETM_DISABLED                0
#define MBEDTLS_SSL_ETM_ENABLED                 1

#define MBEDTLS_SSL_COMPRESS_NULL               0
#define MBEDTLS_SSL_COMPRESS_DEFLATE            1

#define MBEDTLS_SSL_VERIFY_NONE                 0
#define MBEDTLS_SSL_VERIFY_OPTIONAL             1
#define MBEDTLS_SSL_VERIFY_REQUIRED             2
#define MBEDTLS_SSL_VERIFY_UNSET                3 /* Used only for sni_authmode */

#define MBEDTLS_SSL_LEGACY_RENEGOTIATION        0
#define MBEDTLS_SSL_SECURE_RENEGOTIATION        1

#define MBEDTLS_SSL_RENEGOTIATION_DISABLED      0
#define MBEDTLS_SSL_RENEGOTIATION_ENABLED       1

#define MBEDTLS_SSL_ANTI_REPLAY_DISABLED        0
#define MBEDTLS_SSL_ANTI_REPLAY_ENABLED         1

#define MBEDTLS_SSL_RENEGOTIATION_NOT_ENFORCED  -1
#define MBEDTLS_SSL_RENEGO_MAX_RECORDS_DEFAULT  16

#define MBEDTLS_SSL_LEGACY_NO_RENEGOTIATION     0
#define MBEDTLS_SSL_LEGACY_ALLOW_RENEGOTIATION  1
#define MBEDTLS_SSL_LEGACY_BREAK_HANDSHAKE      2

#define MBEDTLS_SSL_TRUNC_HMAC_DISABLED         0
#define MBEDTLS_SSL_TRUNC_HMAC_ENABLED          1
#define MBEDTLS_SSL_TRUNCATED_HMAC_LEN          10  /* 80 bits, rfc 6066 section 7 */

#define MBEDTLS_SSL_SESSION_TICKETS_DISABLED     0
#define MBEDTLS_SSL_SESSION_TICKETS_ENABLED      1

#define MBEDTLS_SSL_CBC_RECORD_SPLITTING_DISABLED    0
#define MBEDTLS_SSL_CBC_RECORD_SPLITTING_ENABLED     1

#define MBEDTLS_SSL_ARC4_ENABLED                0
#define MBEDTLS_SSL_ARC4_DISABLED               1

#define MBEDTLS_SSL_PRESET_DEFAULT              0
#define MBEDTLS_SSL_PRESET_SUITEB               2

#define MBEDTLS_SSL_CERT_REQ_CA_LIST_ENABLED       1
#define MBEDTLS_SSL_CERT_REQ_CA_LIST_DISABLED      0

/*
 * Default range for DTLS retransmission timer value, in milliseconds.
 * RFC 6347 4.2.4.1 says from 1 second to 60 seconds.
 */
#define MBEDTLS_SSL_DTLS_TIMEOUT_DFL_MIN    1000
#define MBEDTLS_SSL_DTLS_TIMEOUT_DFL_MAX   60000

/**
 * \name SECTION: Module settings
 *
 * The configuration options you can set for this module are in this section.
 * Either change them in config.h or define them on the compiler command line.
 * \{
 */

#if !defined(MBEDTLS_SSL_DEFAULT_TICKET_LIFETIME)
#define MBEDTLS_SSL_DEFAULT_TICKET_LIFETIME     86400 /**< Lifetime of session tickets (if enabled) */
#endif

/*
 * Maxium fragment length in bytes,
 * determines the size of each of the two internal I/O buffers.
 *
 * Note: the RFC defines the default size of SSL / TLS messages. If you
 * change the value here, other clients / servers may not be able to
 * communicate with you anymore. Only change this value if you control
 * both sides of the connection and have it reduced at both sides, or
 * if you're using the Max Fragment Length extension and you know all your
 * peers are using it too!
 */
#if !defined(MBEDTLS_SSL_MAX_CONTENT_LEN)
#define MBEDTLS_SSL_MAX_CONTENT_LEN         16384   /**< Size of the input / output buffer */
#endif

/* \} name SECTION: Module settings */

/*
 * Length of the verify data for secure renegotiation
 */

/*
 * Signaling ciphersuite values (SCSV)
 */
#define MBEDTLS_SSL_EMPTY_RENEGOTIATION_INFO    0xFF   /**< renegotiation info ext */
#define MBEDTLS_SSL_FALLBACK_SCSV_VALUE         0x5600 /**< RFC 7507 section 2 */

/*
 * Supported Signature and Hash algorithms (For TLS 1.2)
 * RFC 5246 section 7.4.1.4.1
 */
#define MBEDTLS_SSL_HASH_NONE                0
#define MBEDTLS_SSL_HASH_MD5                 1
#define MBEDTLS_SSL_HASH_SHA1                2
#define MBEDTLS_SSL_HASH_SHA224              3
#define MBEDTLS_SSL_HASH_SHA256              4
#define MBEDTLS_SSL_HASH_SHA384              5
#define MBEDTLS_SSL_HASH_SHA512              6

#define MBEDTLS_SSL_SIG_ANON                 0
#define MBEDTLS_SSL_SIG_RSA                  1
#define MBEDTLS_SSL_SIG_ECDSA                3

/*
 * Client Certificate Types
 * RFC 5246 section 7.4.4 plus RFC 4492 section 5.5
 */
#define MBEDTLS_SSL_CERT_TYPE_RSA_SIGN       1
#define MBEDTLS_SSL_CERT_TYPE_ECDSA_SIGN    64

/*
 * Message, alert and handshake types
 */
#define MBEDTLS_SSL_MSG_CHANGE_CIPHER_SPEC     20
#define MBEDTLS_SSL_MSG_ALERT                  21
#define MBEDTLS_SSL_MSG_HANDSHAKE              22
#define MBEDTLS_SSL_MSG_APPLICATION_DATA       23

#define MBEDTLS_SSL_ALERT_LEVEL_WARNING         1
#define MBEDTLS_SSL_ALERT_LEVEL_FATAL           2

#define MBEDTLS_SSL_ALERT_MSG_CLOSE_NOTIFY           0  /* 0x00 */
#define MBEDTLS_SSL_ALERT_MSG_UNEXPECTED_MESSAGE    10  /* 0x0A */
#define MBEDTLS_SSL_ALERT_MSG_BAD_RECORD_MAC        20  /* 0x14 */
#define MBEDTLS_SSL_ALERT_MSG_DECRYPTION_FAILED     21  /* 0x15 */
#define MBEDTLS_SSL_ALERT_MSG_RECORD_OVERFLOW       22  /* 0x16 */
#define MBEDTLS_SSL_ALERT_MSG_DECOMPRESSION_FAILURE 30  /* 0x1E */
#define MBEDTLS_SSL_ALERT_MSG_HANDSHAKE_FAILURE     40  /* 0x28 */
#define MBEDTLS_SSL_ALERT_MSG_NO_CERT               41  /* 0x29 */
#define MBEDTLS_SSL_ALERT_MSG_BAD_CERT              42  /* 0x2A */
#define MBEDTLS_SSL_ALERT_MSG_UNSUPPORTED_CERT      43  /* 0x2B */
#define MBEDTLS_SSL_ALERT_MSG_CERT_REVOKED          44  /* 0x2C */
#define MBEDTLS_SSL_ALERT_MSG_CERT_EXPIRED          45  /* 0x2D */
#define MBEDTLS_SSL_ALERT_MSG_CERT_UNKNOWN          46  /* 0x2E */
#define MBEDTLS_SSL_ALERT_MSG_ILLEGAL_PARAMETER     47  /* 0x2F */
#define MBEDTLS_SSL_ALERT_MSG_UNKNOWN_CA            48  /* 0x30 */
#define MBEDTLS_SSL_ALERT_MSG_ACCESS_DENIED         49  /* 0x31 */
#define MBEDTLS_SSL_ALERT_MSG_DECODE_ERROR          50  /* 0x32 */
#define MBEDTLS_SSL_ALERT_MSG_DECRYPT_ERROR         51  /* 0x33 */
#define MBEDTLS_SSL_ALERT_MSG_EXPORT_RESTRICTION    60  /* 0x3C */
#define MBEDTLS_SSL_ALERT_MSG_PROTOCOL_VERSION      70  /* 0x46 */
#define MBEDTLS_SSL_ALERT_MSG_INSUFFICIENT_SECURITY 71  /* 0x47 */
#define MBEDTLS_SSL_ALERT_MSG_INTERNAL_ERROR        80  /* 0x50 */
#define MBEDTLS_SSL_ALERT_MSG_INAPROPRIATE_FALLBACK 86  /* 0x56 */
#define MBEDTLS_SSL_ALERT_MSG_USER_CANCELED         90  /* 0x5A */
#define MBEDTLS_SSL_ALERT_MSG_NO_RENEGOTIATION     100  /* 0x64 */
#define MBEDTLS_SSL_ALERT_MSG_UNSUPPORTED_EXT      110  /* 0x6E */
#define MBEDTLS_SSL_ALERT_MSG_UNRECOGNIZED_NAME    112  /* 0x70 */
#define MBEDTLS_SSL_ALERT_MSG_UNKNOWN_PSK_IDENTITY 115  /* 0x73 */
#define MBEDTLS_SSL_ALERT_MSG_NO_APPLICATION_PROTOCOL 120 /* 0x78 */

#define MBEDTLS_SSL_HS_HELLO_REQUEST            0
#define MBEDTLS_SSL_HS_CLIENT_HELLO             1
#define MBEDTLS_SSL_HS_SERVER_HELLO             2
#define MBEDTLS_SSL_HS_HELLO_VERIFY_REQUEST     3
#define MBEDTLS_SSL_HS_NEW_SESSION_TICKET       4
#define MBEDTLS_SSL_HS_CERTIFICATE             11
#define MBEDTLS_SSL_HS_SERVER_KEY_EXCHANGE     12
#define MBEDTLS_SSL_HS_CERTIFICATE_REQUEST     13
#define MBEDTLS_SSL_HS_SERVER_HELLO_DONE       14
#define MBEDTLS_SSL_HS_CERTIFICATE_VERIFY      15
#define MBEDTLS_SSL_HS_CLIENT_KEY_EXCHANGE     16
#define MBEDTLS_SSL_HS_FINISHED                20

/*
 * TLS extensions
 */
#define MBEDTLS_TLS_EXT_SERVERNAME                   0
#define MBEDTLS_TLS_EXT_SERVERNAME_HOSTNAME          0

#define MBEDTLS_TLS_EXT_MAX_FRAGMENT_LENGTH          1

#define MBEDTLS_TLS_EXT_TRUNCATED_HMAC               4

#define MBEDTLS_TLS_EXT_SUPPORTED_ELLIPTIC_CURVES   10
#define MBEDTLS_TLS_EXT_SUPPORTED_POINT_FORMATS     11

#define MBEDTLS_TLS_EXT_SIG_ALG                     13

#define MBEDTLS_TLS_EXT_ALPN                        16

#define MBEDTLS_TLS_EXT_ENCRYPT_THEN_MAC            22 /* 0x16 */
#define MBEDTLS_TLS_EXT_EXTENDED_MASTER_SECRET  0x0017 /* 23 */

#define MBEDTLS_TLS_EXT_SESSION_TICKET              35

#define MBEDTLS_TLS_EXT_ECJPAKE_KKPP               256 /* experimental */

#define MBEDTLS_TLS_EXT_RENEGOTIATION_INFO      0xFF01


#define MBEDTLS_PREMASTER_SIZE     sizeof( union mbedtls_ssl_premaster_secret )

#ifdef __cplusplus
extern "C" {
#endif

/*
 * SSL state machine
 */
typedef enum
{
    MBEDTLS_SSL_HELLO_REQUEST,
    MBEDTLS_SSL_CLIENT_HELLO,
    MBEDTLS_SSL_SERVER_HELLO,
    MBEDTLS_SSL_SERVER_CERTIFICATE,
    MBEDTLS_SSL_SERVER_KEY_EXCHANGE,
    MBEDTLS_SSL_CERTIFICATE_REQUEST,
    MBEDTLS_SSL_SERVER_HELLO_DONE,
    MBEDTLS_SSL_CLIENT_CERTIFICATE,
    MBEDTLS_SSL_CLIENT_KEY_EXCHANGE,
    MBEDTLS_SSL_CERTIFICATE_VERIFY,
    MBEDTLS_SSL_CLIENT_CHANGE_CIPHER_SPEC,
    MBEDTLS_SSL_CLIENT_FINISHED,
    MBEDTLS_SSL_SERVER_CHANGE_CIPHER_SPEC,
    MBEDTLS_SSL_SERVER_FINISHED,
    MBEDTLS_SSL_FLUSH_BUFFERS,
    MBEDTLS_SSL_HANDSHAKE_WRAPUP,
    MBEDTLS_SSL_HANDSHAKE_OVER,
    MBEDTLS_SSL_SERVER_NEW_SESSION_TICKET,
    MBEDTLS_SSL_SERVER_HELLO_VERIFY_REQUEST_SENT,
}
mbedtls_ssl_states;

/**
 * \brief          Callback type: send data on the network.
 *
 * \note           That callback may be either blocking or non-blocking.
 *
 * \param ctx      Context for the send callback (typically a file descriptor)
 * \param buf      Buffer holding the data to send
 * \param len      Length of the data to send
 *
 * \return         The callback must return the number of bytes sent if any,
 *                 or a non-zero error code.
 *                 If performing non-blocking I/O, \c MBEDTLS_ERR_SSL_WANT_WRITE
 *                 must be returned when the operation would block.
 *
 * \note           The callback is allowed to send fewer bytes than requested.
 *                 It must always return the number of bytes actually sent.
 */
typedef int mbedtls_ssl_send_t( void *ctx,
                                const unsigned char *buf,
                                size_t len );


/**
 * \brief          Callback type: receive data from the network, with timeout
 *
 * \note           That callback must block until data is received, or the
 *                 timeout delay expires, or the operation is interrupted by a
 *                 signal.
 *
 * \param ctx      Context for the receive callback (typically a file descriptor)
 * \param buf      Buffer to write the received data to
 * \param len      Length of the receive buffer
 * \param timeout  Maximum nomber of millisecondes to wait for data
 *                 0 means no timeout (potentially waiting forever)
 *
 * \return         The callback must return the number of bytes received,
 *                 or a non-zero error code:
 *                 \c MBEDTLS_ERR_SSL_TIMEOUT if the operation timed out,
 *                 \c MBEDTLS_ERR_SSL_WANT_READ if interrupted by a signal.
 *
 * \note           The callback may receive fewer bytes than the length of the
 *                 buffer. It must always return the number of bytes actually
 *                 received and written to the buffer.
 */
typedef int mbedtls_ssl_recv_timeout_t( void *ctx,
                                        unsigned char *buf,
                                        size_t len,
                                        uint32_t timeout );



#endif /* ssl.h */
