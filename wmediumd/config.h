#ifndef CONFIG_H_
#define CONFIG_H_

int load_config(struct wmediumd *ctx, const char *file, const char *per_file, bool full_dynamic);
int use_fixed_random_value(struct wmediumd *ctx);

#endif /* CONFIG_H_ */
