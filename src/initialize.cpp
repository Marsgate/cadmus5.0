#include "main.h"

static lv_res_t list_release_action(lv_obj_t * list_btn)
{
  printf("List element click:%s\n", lv_list_get_btn_text(list_btn));
  return LV_RES_OK;
}

void initialize(){
  initSlew();

  /*
  lv_obj_t * label1 = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(label1, "Red          Blue");
  lv_obj_align(label1, NULL, LV_ALIGN_CENTER, -100, -10);

  // create a switch
  lv_obj_t * mirrorSwitch = lv_sw_create(lv_scr_act(), NULL);
  lv_obj_align(mirrorSwitch, NULL, LV_ALIGN_CENTER, -100, 40);

  lv_obj_t * list1 = lv_list_create(lv_scr_act(), NULL);
  lv_obj_set_size(list1, 130, 150);
  lv_obj_align(list1, NULL, LV_ALIGN_IN_TOP_RIGHT, -20, 40);

  lv_list_add(list1, NULL, "1. Big Boi", list_release_action);
  lv_list_add(list1, NULL, "2. Skills", list_release_action);
  lv_list_add(list1, NULL, "3. None", list_release_action);
  */
}

void disabled() {}

void competition_initialize() {}
