package cedarx_config

import (
    "android/soong/android"
    "android/soong/cc"
    "fmt"
)
// Add other board config related with Android sdkVersion alike below.
var a100_R_cflags = []string {
    "-DCONF_ANDROID_SUB_VER=1",
    "-DCONF_KERNEL_VERSION_5_4",
    "-DCONF_SIMPLE_ION",
    "-DCONF_GPU_IMG_USE_COMMON_STRUCT",//After ceres, MALI GPU and IMG GPU use the same structure for users
    "-DCONF_KERN_BITWIDE=64",//contradictory with cedarc!!!
    "-DCONF_NEW_BDMV_STREAM",
    "-DCONF_NEW_DISPLAY",
    "-DCONF_H265_4K",
    "-DCONF_ION_HANDLE_INT",
    "-DCONF_VE_PHY_OFFSET=0x00000000",
}
var ceres_cflags = []string {
    "-DCONF_ANDROID_MAJOR_VER=10",
    "-DCONF_ANDROID_SUB_VER=1",
    "-DCONF_KERNEL_VERSION_4_9",
    "-DCONF_GPU_IMG_USE_COMMON_STRUCT",//After ceres, MALI GPU and IMG GPU use the same structure for users
    "-DCONF_KERN_BITWIDE=64",//contradictory with cedarc!!!
    "-DCONF_NEW_BDMV_STREAM",
    "-DCONF_NEW_DISPLAY",
    "-DCONF_H265_4K",
    "-DCONF_ION_HANDLE_INT",
    "-DCONF_VE_PHY_OFFSET=0x00000000",
 
    "-DCONF_6K",
}
var venus_cflags = []string {
    "-DCONF_ANDROID_MAJOR_VER=10",
    "-DCONF_ANDROID_SUB_VER=1",
    "-DCONF_KERNEL_VERSION_4_9",
    "-DCONF_GPU_MALI",
    "-DCONF_KERN_BITWIDE=64",//contradictory with cedarc!!!
    "-DCONF_NEW_BDMV_STREAM",
    "-DCONF_NEW_DISPLAY",
    "-DCONF_H264_4K_P2P",
    "-DCONF_H265_4K",
    "-DCONF_H265_4K_P2P",
    "-DCONF_ION_HANDLE_INT",
    "-DCONF_VE_PHY_OFFSET=0x00000000",
    //"-DCONF_AFBC_ENABLE",
    "-DCONF_6K",
}
var t3_cflags = []string {
    "-DCONF_ANDROID_MAJOR_VER=10",
    "-DCONF_ANDROID_SUB_VER=1",
    "-DCONF_KERNEL_VERSION_4_9",
    "-DCONF_GPU_MALI",
    "-DCONF_KERN_BITWIDE=32",//contradictory with cedarc!!!
    "-DCONF_NEW_BDMV_STREAM",
    "-DCONF_NEW_DISPLAY",
    "-DCONF_ION_HANDLE_INT",
    "-DCONF_VE_PHY_OFFSET=0x40000000",
    "-DCONF_WMV12VP6_1080P",
    //"-DCONF_AFBC_ENABLE",
    "-DCONF_6K",
}

var dolphin_cflags = []string {
    "-DCONF_ANDROID_MAJOR_VER=10",
    "-DCONF_ANDROID_SUB_VER=1",
    "-DCONF_KERNEL_VERSION_4_9",
    "-DCONF_GPU_MALI",
    "-DCONF_KERN_BITWIDE=32",
    "-DCONF_NEW_BDMV_STREAM",
    "-DCONF_NEW_DISPLAY",
    "-DCONF_ION_HANDLE_INT",
    "-DCONF_VE_PHY_OFFSET=0x40000000",
    "-DCONF_NEW_BDMV_STREAM",
    "-DCONF_PRODUCT_STB",
    "-DCONF_PTS_TOSF",
    "-DCONF_H265_4K_P2P",
    "-DCONF_H265_4K",
    "-DCONF_3D_ENABLE",
    "-DCONF_6K",
}

var cupid_cflags = []string {
    "-DCONF_ANDROID_MAJOR_VER=10",
    "-DCONF_ANDROID_SUB_VER=1",
    "-DCONF_KERNEL_VERSION_4_9",
    "-DCONF_GPU_MALI",
    "-DCONF_KERN_BITWIDE=64",
    "-DCONF_NEW_BDMV_STREAM",
    "-DCONF_NEW_DISPLAY",
    "-DCONF_ION_HANDLE_INT",
    "-DCONF_VE_PHY_OFFSET=0x00000000",
    "-DCONF_NEW_BDMV_STREAM",
    "-DCONF_PRODUCT_STB",
    "-DCONF_PTS_TOSF",
    "-DCONF_H265_4K_P2P",
    "-DCONF_H264_4K_P2P",
    "-DCONF_VP9_4K_P2P",
    "-DCONF_AVS2_4K_P2P",
    "-DCONF_H265_4K",
    "-DCONF_3D_ENABLE",
    "-DCONF_USE_IOMMU",
    "-DCONF_AFBC_ENABLE",
    "-DCONF_HIGH_DYNAMIC_RANGE_ENABLE",
    "-DCONF_DI_300_SUPPORT",
    "-DCONF_SCALE_DOWN",
    "-DCONF_6K",
}

var mercury_cflags = []string {
    "-DCONF_ANDROID_MAJOR_VER=10",
    "-DCONF_ANDROID_SUB_VER=1",
    "-DCONF_KERNEL_VERSION_4_9",
    "-DCONF_GPU_MALI",
    "-DCONF_KERN_BITWIDE=64",
    "-DCONF_NEW_BDMV_STREAM",
    "-DCONF_NEW_DISPLAY",
    "-DCONF_ION_HANDLE_INT",
    "-DCONF_VE_PHY_OFFSET=0x00000000",
    "-DCONF_NEW_BDMV_STREAM",
    "-DCONF_PRODUCT_STB",
    "-DCONF_PTS_TOSF",
    //"-DCONF_H265_4K_P2P",
    //"-DCONF_H264_4K_P2P",
    //"-DCONF_VP9_4K_P2P",
    //"-DCONF_AVS2_4K_P2P",
    "-DCONF_H265_4K",
    "-DCONF_3D_ENABLE",
    "-DCONF_USE_IOMMU",
    "-DCONF_AFBC_ENABLE",
    "-DCONF_HIGH_DYNAMIC_RANGE_ENABLE",
    "-DCONF_DI_300_SUPPORT",
    "-DCONF_SCALE_DOWN",
}

var default_cflags = []string {
    "-DCONF_ANDROID_MAJOR_VER=10",
    "-DCONF_ANDROID_SUB_VER=1",
    "-DCONF_KERNEL_VERSION_4_9",
    "-DCONF_GPU_MALI",
    "-DCONF_KERN_BITWIDE=32",//contradictory with cedarc!!!
    "-DCONF_NEW_BDMV_STREAM",
    "-DCONF_NEW_DISPLAY",
    "-DCONF_ION_HANDLE_INT",
    "-DCONF_VE_PHY_OFFSET=0x40000000",
    //"-DCONF_AFBC_ENABLE",
    "-DCONF_6K",
}
func globalDefaults(ctx android.BaseContext) ([]string) {
    var cppflags []string

    sdkVersion := ctx.AConfig().PlatformSdkVersionInt()
    fmt.Println("sdkVersion:", sdkVersion)

    if sdkVersion >= 30 {
        cppflags = append(cppflags,"-DCONF_Q_AND_NEWER")
        cppflags = append(cppflags, "-DCONF_R_AND_NEWER")
        cppflags = append(cppflags, "-DCONF_ANDROID_MAJOR_VER=11")
        board := ctx.AConfig().VendorConfig("vendor").String("board")
        cppflags = append(cppflags,"-DTARGET_BOARD_PLATFORM="+board)
        fmt.Println("board:",board)
        switch board{
            case "venus":
                cppflags = append(cppflags,venus_cflags...)
            case "ceres":
                cppflags = append(cppflags,a100_R_cflags...)
            case "t3":
                cppflags = append(cppflags,t3_cflags...)
            case "dolphin":
                cppflags = append(cppflags,dolphin_cflags...)
            case "cupid":
                cppflags = append(cppflags,cupid_cflags...)
            case "mercury":
                cppflags = append(cppflags,mercury_cflags...)
            default:
                cppflags = append(cppflags,default_cflags...)
                fmt.Println("board config has NOT been set. Please check it.")
        }
    } else if sdkVersion >= 29 { //after Q
        cppflags = append(cppflags,"-DCONF_Q_AND_NEWER")
        cppflags = append(cppflags, "-DCONF_ANDROID_MAJOR_VER=10")
        board := ctx.AConfig().VendorConfig("vendor").String("board")
        cppflags = append(cppflags,"-DTARGET_BOARD_PLATFORM="+board)
        fmt.Println("board:",board)
        switch board{
            case "venus":
                cppflags = append(cppflags,venus_cflags...)
            case "ceres":
                cppflags = append(cppflags,ceres_cflags...)
            case "t3":
                cppflags = append(cppflags,t3_cflags...)
            case "dolphin":
                cppflags = append(cppflags,dolphin_cflags...)
            case "cupid":
                cppflags = append(cppflags,cupid_cflags...)
            case "mercury":
                cppflags = append(cppflags,mercury_cflags...)
            default:
                cppflags = append(cppflags,default_cflags...)
                fmt.Println("board config has NOT been set. Please check it.")
        }
    }
    if sdkVersion >= 28 { //after P
        cppflags = append(cppflags,"-DCONF_PIE_AND_NEWER")
    }
    if sdkVersion >= 26 { //after O
        cppflags = append(cppflags,"-DCONF_OREO_AND_NEWER")
    }
    if sdkVersion >= 24 { //after N
        cppflags = append(cppflags,"-DCONF_NOUGAT_AND_NEWER")
    }
    if sdkVersion >= 23 { //after M
        cppflags = append(cppflags,"-DCONF_MARSHMALLOW_AND_NEWER")
    }
    if sdkVersion >= 21 { //after L
        cppflags = append(cppflags,"-DCONF_LOLLIPOP_AND_NEWER")
    }
    if sdkVersion >= 19 { //after KK
        cppflags = append(cppflags,"-DCONF_KITKAT_AND_NEWER")
    }
    if sdkVersion >= 17 { //after JB42
        cppflags = append(cppflags,"-DCONF_JB42_AND_NEWER")
    }

    config  := ctx.Config().VendorConfig("gpu").String("public_include_file")
    cppflags = append(cppflags, "-DGPU_PUBLIC_INCLUDE=\"" + config + "\"")

    return cppflags
}

func configDefaults(ctx android.LoadHookContext) {
    type props struct {
        Cflags []string
    }
    p := &props{}
    p.Cflags = globalDefaults(ctx)
    ctx.AppendProperties(p)
}

func configDefaultsFactory() android.Module {
    module := cc.DefaultsFactory()
    android.AddLoadHook(module, configDefaults)
    return module
}

func init() {
    fmt.Println("cedarx config go file start")
    android.RegisterModuleType("cedarx_config_defaults", configDefaultsFactory)
}
