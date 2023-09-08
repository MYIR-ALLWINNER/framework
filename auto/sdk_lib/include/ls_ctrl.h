#ifndef LS_CTRL_H
#define LS_CTRL_H
#ifdef __cplusplus
extern "C" {
#endif

/*      APIs     */
/* audio mute */
int audio_ctrl_init(void);
int audio_on(void);
int audio_volume_set(int level);
int audio_off(void);
void audio_ctrl_exit(void);

/*lcd black power*/
int lcd_power_ctrl_init(void);
int lcd_on(void);
int lcd_off(void);
void lcd_power_ctrl_exit(void);

/* lcd brightness */
int lcd_blk_ctrl_init(void);
int lcd_blk_ctrl(unsigned long val);
void lcd_blk_ctrl_exit(void);

int lock_file_rename(int camera_id, int idx, const char *type,int new_idx);
/*system update */


//int check_update(const char *dir, const char** key, int num, char **name);
//int system_update(const char **name, int num);
int check_update(const char *version);
int system_update(char *ver);
int ls_reboot(void);

#ifdef __cplusplus
}
#endif


#endif  /* LS_CTRL_H */


