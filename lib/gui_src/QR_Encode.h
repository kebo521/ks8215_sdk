// QR_Encode.h : CQR_Encode クラス宣言およびインターフェイス定義
// Date 2006/05/17	Ver. 1.22	Psytec Inc.
// Date 2015/11/18	fuqing change for  k21.

#ifndef __QR_ENCDOE_H__
#define __QR_ENCDOE_H__

#ifdef __cplusplus
extern "C" {
#endif

	// 誤り訂正レベル
	#define QR_LEVEL_L				0
	#define QR_LEVEL_M				1
	#define QR_LEVEL_Q				2
	#define QR_LEVEL_H				3

	// データモード
	#define QR_MODE_NUMERAL		0
	#define QR_MODE_ALPHABET		1
	#define QR_MODE_8BIT					2
	#define QR_MODE_KANJI				3

	// バージョン(型番)グループ
	#define QR_VRESION_S					0				// 1 〜 9
	#define QR_VRESION_M				1				// 10 〜 26
	#define QR_VRESION_L					2				// 27 〜 40

#if 0	

	--<OEM Size>--
	#define MAX_ALLCODEWORD		3706			// 総コードワード数最大値
	#define MAX_DATACODEWORD	2956			// データコードワード最大値(バージョン40-L)
	#define MAX_CODEBLOCK			153				// ブロックデータコードワード数最大値(ＲＳコードワードを含む)
	#define MAX_MODULESIZE			177				// 一辺モジュール数最大値

#else

		// 21:Version=1,ﾗ�ｴ�ﾗﾖｷ�=17(8.5ｸ�ｺｺﾗﾖ)
		// 25:Version=2,ﾗ�ｴ�ﾗﾖｷ�=32(16ｸ�ｺｺﾗﾖ)
		// 29:Version=3,ﾗ�ｴ�ﾗﾖｷ�=49(24.5ｸ�ｺｺﾗﾖ)
		// 33:Version=4,ﾗ�ｴ�ﾗﾖｷ�=78(39ｸ�ｺｺﾗﾖ)
		// 37:Version=5,ﾗ�ｴ�ﾗﾖｷ�=106(53ｸ�ｺｺﾗﾖ) 
		// 41:Version=6,ﾗ�ｴ�ﾗﾖｷ�=134(67ｸ�ｺｺﾗﾖ)
		// 45:Version=7,ﾗ�ｴ�ﾗﾖｷ�=154(77ｸ�ｺｺﾗﾖ)
		// 49:Version=8,ﾗ�ｴ�ﾗﾖｷ�=192(96ｸ�ｺｺﾗﾖ)

	#define MAX_MODULESIZE			49				
	#define MAX_ALLCODEWORD		(MAX_MODULESIZE*20)	
	#define MAX_DATACODEWORD	(MAX_MODULESIZE*19)	
	#define MAX_CODEBLOCK			153	
		
	//106 1122222222222222222222222222222222233333333333333333333333333333333333333333333333334345444444444444444567
	//134 11222222222222222222222222222222222333333333333333333333333333333333344554445345353455333333333345435535333333334345444444444444444567

#endif

	// ビットマップ描画時マージン
	#define QR_MARGIN			4


	/////////////////////////////////////////////////////////////////////////////
	typedef struct tagRS_BLOCKINFO
	{
		int ncRSBlock;			// ＲＳブロック数
		int ncAllCodeWord;		// ブロック内コードワード数
		int ncDataCodeu32;		// データコードワード数(コードワード数 - ＲＳコードワード数)

	} RS_BLOCKINFO, *LPRS_BLOCKINFO;


	/////////////////////////////////////////////////////////////////////////////
	// QRコードバージョン(型番)関連情報

	typedef struct tagQR_VERSIONINFO
	{
		int nVersionNo;					// バージョン(型番)番号(1〜40)
		int ncAllCodeWord;				// 総コードワード数

										// 以下配列添字は誤り訂正率(0 = L, 1 = M, 2 = Q, 3 = H) 
		int ncDataCodeu32[4];			// データコードワード数(総コードワード数 - ＲＳコードワード数)

		int ncAlignPoint;				// アライメントパターン座標数
		int nAlignPoint[6];				// アライメントパターン中心座標

		RS_BLOCKINFO RS_BlockInfo1[4];	// ＲＳブロック情報(1)
		RS_BLOCKINFO RS_BlockInfo2[4];	// ＲＳブロック情報(2)

	} QR_VERSIONINFO, *LPQR_VERSIONINFO;


	/////////////////////////////////////////////////////////////////////////////
	// CQR_Encode クラス
	
    typedef struct
    {
		int 	nLevel;				// 誤り訂正レベル
		int 	nVersion;			// バージョン(型番)
		int 	bAutoExtent;		// バージョン(型番)自動拡張指定フラグ
		int 	nMaskingNo;			// マスキングパターン番号
	
		int 	nSymbleSize;
		u8 		byModuleData[MAX_MODULESIZE][MAX_MODULESIZE]; // [x][y]
		// bit5:機能モジュール（マスキング対象外）フラグ
		// bit4:機能モジュール描画データ
		// bit1:エンコードデータ
		// bit0:マスク後エンコード描画データ
		// 20hとの論理和により機能モジュール判定、11hとの論理和により描画（最終的にはBOOL値化）
	
		int 	ncDataCodeu32Bit;					// データコードワードビット長
		u8 		byDataCodeu32[MAX_DATACODEWORD];	// 入力データエンコードエリア
	
		int 	ncDataBlock;
		u8 		byBlockMode[MAX_DATACODEWORD];
		int 	nBlockLength[MAX_DATACODEWORD];
	
		int 	ncAllCodeWord;						// 総コードワード数(ＲＳ誤り訂正データを含む)
		u8 		byAllCodeWord[MAX_ALLCODEWORD];		// 総コードワード算出エリア
		u8 		byRSWork[MAX_CODEBLOCK];			// ＲＳコードワード算出ワーク
    }QR_DATA;
	//extern QR_DATA 	QR_gData;

// データエンコード関連ファンクション

	int EncodeData(int nLevel, int nVersion, int bAutoExtent, int nMaskingNo, const char* lpsSource, int ncSource );//<q>private:
	int GetEncodeVersion(int nVersion, const char* lpsSource, int ncLength);
	int EncodeSourceData(const char* lpsSource, int ncLength, int nVerGroup);

	int GetBitLength(u8 nMode, int ncData, int nVerGroup);

	int SetBitStream(int nIndex, u32 wData, int ncData);

	int IsNumeralData(unsigned char c);
	int IsAlphabetData(unsigned char c);
	int IsKanjiData(unsigned char c1, unsigned char c2);

	u8 AlphabetToBinaly(unsigned char c);
	u32 KanjiToBinaly(u32 wc);

	void GetRSCodeu32(u8* lpbyRSWork, int ncDataCodeu32, int ncRSCodeu32);

// モジュール配置関連ファンクション

	//void FormatModule();

	//void SetFunctionModule();
	void SetFinderPattern(int x, int y);
	void SetAlignmentPattern(int x, int y);
	//void SetVersionPattern();
	//void SetCodeu32Pattern();
	void SetMaskingPattern(int nPatternNo);
	void SetFormatInfoPattern(int nPatternNo);
	//int  CountPenalty();



	
	/**
	 * ﾉ�ｳﾉｶ�ﾎｬﾂ�ﾍｼﾆｬﾎﾄｼ�
	 *
	 * @param pInfo			[in]					ﾐ靨ｪﾉ�ｳﾉｵﾄﾊ�ｾﾝﾐﾅﾏ｢ﾊ�ｾﾝ
	 * @param nLen			[in]					ﾐ靨ｪﾉ�ｳﾉｵﾄﾊ�ｾﾝﾐﾅﾏ｢ﾊ�ｾﾝｳ､ｶﾈ
	 * @param bHighQuality	[in]					ﾊﾇｷ�ﾉ�ｳﾉｸﾟﾖﾊﾁｿｶ�ﾎｬﾂ�｣ｬYESﾎｪｸﾟﾖﾊﾁｿﾐｧｹ�｣ｬNOﾎｪﾆﾕﾍｨﾐｧｹ�
	 * @param nScale		[in]					ｶ�ﾎｬﾂ�ﾍｼﾆｬｷﾅｴ�ｱｶﾊ�
	 * @param pImgFile		[in]					ｶ�ﾎｬﾂ�ﾍｼﾆｬﾎﾄｼ�ﾃ�
	 * @param pImgWidth		[out]					ｶ�ﾎｬﾂ�ﾍｼﾆｬｿ�ｶﾈ
	 * @retval {@link RET_OK}  						ｳﾉｹｦ
	 * @retval {@link RET_ERR}						ｴ�ﾎ�
	 */
	extern int Lib_QrCodeImg(IMAGE *rImge,const char* pInfo ,int bHighQuality);



#ifdef __cplusplus
}
#endif

#endif
