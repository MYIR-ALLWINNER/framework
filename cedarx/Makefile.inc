
CFLAGS_CDXG = -g -Wall -D_GNU_SOURCE -DCONF_H265_4K \
                        -DCONF_KERNEL_VERSION_4_9 \
                        -DCONF_GPU_MALI \
                        -DCONF_KERN_BITWIDE=64 \
                        -DCONF_NEW_BDMV_STREAM \
                        -DCONF_NEW_DISPLAY \
                        -DCONF_ION_HANDLE_INT \
                        -DCONF_VE_PHY_OFFSET \
                        -DCONF_PRODUCT_STB \
                        -DCONF_3D_ENABLE \
                        -DCONF_USE_IOMMU \
                        -DCONF_AFBC_ENABLE \
                        -DCONF_HIGH_DYNAMIC_RANGE_ENABLE \
                        -DCONF_SCALE_DOWN \
			  -Wno-unused-variable \
			  -Wno-unused-result \
			  -Wno-unused-function \
			  -Wno-unused-value \
			  -Wno-pointer-to-int-cast \
			  -Wno-int-to-pointer-cast \
			  -Wno-unused-label \
			  -Wno-strict-aliasing \
			  -Wno-unused-but-set-variable 
              # -Werror
CPPFLAGS_CDXG = -g -Wall -Werror -D_GNU_SOURCE \
				-Wno-unused-variable \
				-Wno-unused-but-set-variable \
			    -Wno-unused-value \
			    -Wno-unused-result 

LDFLAGS_CDXG = -Wl,--no-undefined -avoid-version

