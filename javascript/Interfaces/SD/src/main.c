#include "mgos.h"
#include "mgos_jsar.h"
#include "mgos_sd.h"

struct mgos_sd *s_sd = NULL;

enum mgos_app_init_result mgos_app_init(void)
{
  mgos_jsar_enableSDPortSpiMode();

  s_sd = mgos_sd_open(false , "/sd_card", 0);

  if (NULL != s_sd) {
    LOG(LL_INFO, ("SD init successfuly!"));

    /* Print card info*/
    struct mbuf jsmb;
    struct json_out jsout = JSON_OUT_MBUF(&jsmb);

    mbuf_init(&jsmb, 0);
    mgos_sd_print_info(&jsout);
    LOG(LL_INFO, ("%.*s", jsmb.len, jsmb.buf));
    

/*
    LOG(LL_INFO, ("SD size=%llu B", mgos_sd_get_fs_size(SD_FS_UNIT_BYTES)));
    LOG(LL_INFO,
        ("SD size=%llu kiB", mgos_sd_get_fs_size(SD_FS_UNIT_KILOBYTES)));
*/
    LOG(LL_INFO,
        ("SD size = %llu MiB", mgos_sd_get_fs_size(SD_FS_UNIT_MEGABYTES)));

    /* Create dir */
    int err = mkdir("/sd_card/dir", 0777);
    LOG(LL_INFO, ("Mkdir: %d", err));
    
    err = rmdir("/sd_card/dir");
    LOG(LL_INFO, ("rmdir: %d", err));

  

    /* Print card files */
    struct json_out jsout1 = JSON_OUT_MBUF(&jsmb);
    mbuf_init(&jsmb, 0);
    mgos_sd_list("", &jsout1);
    LOG(LL_INFO, ("%.*s", jsmb.len, jsmb.buf));
    mbuf_free(&jsmb);
  

    /* Test write/read file */
    const char *fname = "/sd_card/test.txt";

    /* ^ Write  */
    FILE *f = fopen(fname, "w");
    const char *txt = "This is a test\n";
    size_t txt_len = strlen(txt);

    LOG(LL_INFO, ("Write file"));

    if (f != NULL) {
      size_t written = fwrite(txt, 1, txt_len, f);
      fclose(f);
      LOG(LL_INFO, ("written: %d, txt_len: %d", (int) written, (int) txt_len));
    } else {
      LOG(LL_ERROR, ("Failed to open %s for writing!", fname));
    }

    /* ^ Read  */
    f = fopen(fname, "r");

    LOG(LL_INFO, ("Read file"));

    if (f != NULL) {
      char buf[64];
      size_t read = fread(buf, 1, txt_len, f);

      fclose(f);

      LOG(LL_INFO, ("read: %d, txt_len: %d", (int) read, (int) txt_len));
    } else {
      LOG(LL_ERROR, ("Failed to open %s for reading!", fname));
    }



  } else {
    LOG(LL_INFO, ("SD init ERROR!"));
  }

 
  return MGOS_APP_INIT_SUCCESS;
}