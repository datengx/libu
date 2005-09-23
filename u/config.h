/* 
 * Copyright (c) 2005, KoanLogic s.r.l. - All rights reserved.  
 */

#ifndef _U_CONFIG_H_
#define _U_CONFIG_H_

struct u_config_s;
typedef struct u_config_s u_config_t;

int u_config_create(u_config_t **pc);
int u_config_free(u_config_t *c);
int u_config_load(u_config_t *c, int fd, int overwrite);

const char* u_config_get_key(u_config_t *c);
const char* u_config_get_value(u_config_t *c);

int u_config_get_subkey(u_config_t *c, const char *subkey, u_config_t **pc);
int u_config_get_subkey_nth(u_config_t *c,const char *subkey, int n, 
    u_config_t **pc);

const char* u_config_get_subkey_value(u_config_t *c, const char *subkey);

int u_config_add_key(u_config_t *c, const char *key, const char *val);
int u_config_set_key(u_config_t *c, const char *key, const char *val);

int u_config_add_child(u_config_t *c, const char *key, u_config_t **pc);
u_config_t* u_config_get_child_n(u_config_t *c, const char *key, int n);
u_config_t* u_config_get_child(u_config_t *c, const char *key);

void u_config_print(u_config_t *c, int lev);

#endif /* !_U_CONFIG_H_ */