#ifndef __G2DAPI_H__
#define __G2DAPI_H__

#ifdef __cplusplus
extern "C" {
#endif

namespace g2dapi
{

typedef struct RECT
{
    int left;
    int top;
    int width;            // preview width
    int height;            // preview height
}stRECT;

typedef enum {
    G2D_ROTATE90,
    G2D_ROTATE180,
    G2D_ROTATE270,
    G2D_FLIP_HORIZONTAL,
    G2D_FLIP_VERTICAL,
    G2D_MIRROR45,
    G2D_MIRROR135,
}g2dRotateAngle;

typedef enum {
	G2D_FORMAT_ARGB8888,
	G2D_FORMAT_ABGR8888,
	G2D_FORMAT_RGBA8888,
	G2D_FORMAT_BGRA8888,
	G2D_FORMAT_XRGB8888,
	G2D_FORMAT_XBGR8888,
	G2D_FORMAT_RGBX8888,
	G2D_FORMAT_BGRX8888,
	G2D_FORMAT_RGB888,
	G2D_FORMAT_BGR888,
	G2D_FORMAT_RGB565,
	G2D_FORMAT_BGR565,
	G2D_FORMAT_ARGB4444,
	G2D_FORMAT_ABGR4444,
	G2D_FORMAT_RGBA4444,
	G2D_FORMAT_BGRA4444,
	G2D_FORMAT_ARGB1555,
	G2D_FORMAT_ABGR1555,
	G2D_FORMAT_RGBA5551,
	G2D_FORMAT_BGRA5551,
	G2D_FORMAT_ARGB2101010,
	G2D_FORMAT_ABGR2101010,
	G2D_FORMAT_RGBA1010102,
	G2D_FORMAT_BGRA1010102,

	/* invailed for UI channel */
	G2D_FORMAT_IYUV422_V0Y1U0Y0 = 0x20,
	G2D_FORMAT_IYUV422_Y1V0Y0U0,
	G2D_FORMAT_IYUV422_U0Y1V0Y0,
	G2D_FORMAT_IYUV422_Y1U0Y0V0,

	G2D_FORMAT_YUV422UVC_V1U1V0U0,
	G2D_FORMAT_YUV422UVC_U1V1U0V0,
	G2D_FORMAT_YUV422_PLANAR,

	G2D_FORMAT_YUV420UVC_V1U1V0U0 = 0x28,
	G2D_FORMAT_YUV420UVC_U1V1U0V0,
	G2D_FORMAT_YUV420_PLANAR,

	G2D_FORMAT_YUV411UVC_V1U1V0U0 = 0x2c,
	G2D_FORMAT_YUV411UVC_U1V1U0V0,
	G2D_FORMAT_YUV411_PLANAR,

	G2D_FORMAT_Y8 = 0x30,

	/* YUV 10bit format */
	G2D_FORMAT_YVU10_P010 = 0x34,

	G2D_FORMAT_YVU10_P210 = 0x36,

	G2D_FORMAT_YVU10_444 = 0x38,
	G2D_FORMAT_YUV10_444 = 0x39,
	G2D_FORMAT_MAX,
} g2d_fmt_enh_usr;

typedef enum {
	/* share data format */
	G2D_FMT_ARGB_AYUV8888	= (0x0),
	G2D_FMT_BGRA_VUYA8888	= (0x1),
	G2D_FMT_ABGR_AVUY8888	= (0x2),
	G2D_FMT_RGBA_YUVA8888	= (0x3),

	G2D_FMT_XRGB8888		= (0x4),
	G2D_FMT_BGRX8888		= (0x5),
	G2D_FMT_XBGR8888		= (0x6),
	G2D_FMT_RGBX8888		= (0x7),

	G2D_FMT_ARGB4444		= (0x8),
	G2D_FMT_ABGR4444		= (0x9),
	G2D_FMT_RGBA4444		= (0xA),
	G2D_FMT_BGRA4444		= (0xB),

	G2D_FMT_ARGB1555		= (0xC),
	G2D_FMT_ABGR1555		= (0xD),
	G2D_FMT_RGBA5551		= (0xE),
	G2D_FMT_BGRA5551		= (0xF),

	G2D_FMT_RGB565			= (0x10),
	G2D_FMT_BGR565			= (0x11),

	G2D_FMT_IYUV422			= (0x12),

	G2D_FMT_8BPP_MONO		= (0x13),
	G2D_FMT_4BPP_MONO		= (0x14),
	G2D_FMT_2BPP_MONO		= (0x15),
	G2D_FMT_1BPP_MONO		= (0x16),

	G2D_FMT_PYUV422UVC		= (0x17),
	G2D_FMT_PYUV420UVC		= (0x18),
	G2D_FMT_PYUV411UVC		= (0x19),

	/* just for output format */
	G2D_FMT_PYUV422			= (0x1A),
	G2D_FMT_PYUV420			= (0x1B),
	G2D_FMT_PYUV411			= (0x1C),

	/* just for input format */
	G2D_FMT_8BPP_PALETTE	= (0x1D),
	G2D_FMT_4BPP_PALETTE	= (0x1E),
	G2D_FMT_2BPP_PALETTE	= (0x1F),
	G2D_FMT_1BPP_PALETTE	= (0x20),

	G2D_FMT_PYUV422UVC_MB16	= (0x21),
	G2D_FMT_PYUV420UVC_MB16	= (0x22),
	G2D_FMT_PYUV411UVC_MB16	= (0x23),
	G2D_FMT_PYUV422UVC_MB32	= (0x24),
	G2D_FMT_PYUV420UVC_MB32	= (0x25),
	G2D_FMT_PYUV411UVC_MB32	= (0x26),
	G2D_FMT_PYUV422UVC_MB64	= (0x27),
	G2D_FMT_PYUV420UVC_MB64	= (0x28),
	G2D_FMT_PYUV411UVC_MB64	= (0x29),
	G2D_FMT_PYUV422UVC_MB128 = (0x2A),
	G2D_FMT_PYUV420UVC_MB128 = (0x2B),
	G2D_FMT_PYUV411UVC_MB128 = (0x2C),

} g2d_data_fmt_usr;

/* BLD LAYER ALPHA MODE*/
typedef enum {
	G2D_PIXEL_ALPHA,
	G2D_GLOBAL_ALPHA,
	G2D_MIXER_ALPHA,
} g2d_alpha_mode_enh_usr;

typedef struct {
	g2d_fmt_enh_usr	 format;
	__u32		 	 width;
	__u32		 	 height;
	__u32		 	 align[3];
	stRECT	 	 	 clip_rect;
	__u8		 	 alpha;
	g2d_alpha_mode_enh_usr mode;
	int		 	 fd;
	__u32 		 use_phy_addr;
} g2d_image_user;

typedef enum {
	G2D_BLT_NONE_H = 0x0,
	G2D_BLT_BLACKNESS,
	G2D_BLT_NOTMERGEPEN,
	G2D_BLT_MASKNOTPEN,
	G2D_BLT_NOTCOPYPEN,
	G2D_BLT_MASKPENNOT,
	G2D_BLT_NOT,
	G2D_BLT_XORPEN,
	G2D_BLT_NOTMASKPEN,
	G2D_BLT_MASKPEN,
	G2D_BLT_NOTXORPEN,
	G2D_BLT_NOP,
	G2D_BLT_MERGENOTPEN,
	G2D_BLT_COPYPEN,
	G2D_BLT_MERGEPENNOT,
	G2D_BLT_MERGEPEN,
	G2D_BLT_WHITENESS = 0x000000ff,

	G2D_ROT_90  = 0x00000100,
	G2D_ROT_180 = 0x00000200,
	G2D_ROT_270 = 0x00000300,
	G2D_ROT_0   = 0x00000400,
	G2D_ROT_H = 0x00001000,
	G2D_ROT_V = 0x00002000,

/*	G2D_SM_TDLR_1  =    0x10000000, */
	G2D_SM_DTLR_1 = 0x10000000,
/*	G2D_SM_TDRL_1  =    0x20000000, */
/*	G2D_SM_DTRL_1  =    0x30000000, */
} g2d_blt_flags_h_usr;

/* Porter Duff BLD command*/
typedef enum {
	G2D_BLD_CLEAR = 0x00000001,
	G2D_BLD_COPY = 0x00000002,
	G2D_BLD_DST = 0x00000003,
	G2D_BLD_SRCOVER = 0x00000004,
	G2D_BLD_DSTOVER = 0x00000005,
	G2D_BLD_SRCIN = 0x00000006,
	G2D_BLD_DSTIN = 0x00000007,
	G2D_BLD_SRCOUT = 0x00000008,
	G2D_BLD_DSTOUT = 0x00000009,
	G2D_BLD_SRCATOP = 0x0000000a,
	G2D_BLD_DSTATOP = 0x0000000b,
	G2D_BLD_XOR = 0x0000000c,
	G2D_CK_SRC = 0x00010000,
	G2D_CK_DST = 0x00020000,
} g2d_bld_cmd_flag_usr;

#if 0
struct G2dOpsS{
    int (*fpG2dInit)();
    int (*fpG2dUnit)(int g2dHandle);
    int (*fpG2dScale)(int g2dHandle,unsigned char *src, int src_width, int src_height, unsigned char *dst, int dst_width, int dst_height);
    int (*fpG2dClip)(int g2dHandle,void* psrc, int src_w, int src_h, int src_x, int src_y, int width, int height, void* pdst, int dst_w, int dst_h, int dst_x, int dst_y);
    int (*fpG2dRotate)(int g2dHandle,g2dRotateAngle angle, unsigned char *src, int src_width, int src_height, unsigned char *dst, int dst_width, int dst_height);

    int (*g2dFormatConv)(int g2dHandle,void* psrc, int src_format,int src_w, int src_h, 
                    int src_crop_x, int src_crop_y, int src_crop_w, int src_crop_h, 
                    void* pdst, int dst_format,int dst_w, int dst_h, 
                    int dst_crop_x, int dst_crop_y,int dst_crop_w, int dst_crop_h);
};

struct G2dOpsS* GetG2dOpsS();
#endif

int g2dInit();
int g2dUnit(int g2dHandle);
int g2dClip(int g2dHandle,void* psrc, int src_w, int src_h, int src_x, int src_y, int width, int height, void* pdst, int dst_w, int dst_h, int dst_x, int dst_y);
int g2dScale(int g2dHandle,unsigned char *src, int src_width, int src_height, unsigned char *dst, int dst_width, int dst_height);
int g2dRotate(int g2dHandle,g2dRotateAngle angle, unsigned char *src, int src_width, int src_height, unsigned char *dst, int dst_width, int dst_height);

int g2dFormatConv(int g2dHandle,void* psrc, int src_format,int src_w, int src_h, 
                    int src_crop_x, int src_crop_y, int src_crop_w, int src_crop_h, 
                    void* pdst, int dst_format,int dst_w, int dst_h, 
                    int dst_crop_x, int dst_crop_y,int dst_crop_w, int dst_crop_h);
#if 0
int g2dflip(int g2dHandle,g2d_blt_flags_h_usr flag,
			int src_sharefd, g2d_fmt_enh_usr src_format,int src_w, int src_h,stRECT src_rect, 
            int dst_sharefd, g2d_fmt_enh_usr dst_format,int dst_w, int dst_h,stRECT dst_rect );
int g2dBlt(int g2dHandle,g2d_blt_flags_h_usr flag_h, g2d_image_user src, g2d_image_user dst);
int g2dBlending(int g2dHandle,g2d_bld_cmd_flag_usr bld_cmd, g2d_image_user src, g2d_image_user dst);
#endif
int g2dClipByFd(int g2dHandle, int inFd,int flag, int infmt,int src_w,int src_h,int src_x,int src_y,int src_width,int src_height,
			int outFd,int outfmt,int dst_w,int dst_h,int dst_x,int dst_y,int dst_width,int dst_height);
}

#ifdef __cplusplus
}
#endif

#endif
