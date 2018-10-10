/*
 *
 * force disable charging (for longer gaming sessions)
 * based on fastcharge.c implementation by Flar2(Aaron seagart)
 * 
 *   0 - disabled (default and charging is on)
 *   1 - Charging is disabled but power is drawn from pmic and adapter to power the tablet, not the battery 
 *
*/
 #include <linux/kobject.h>
#include <linux/sysfs.h>
#include <linux/string.h>
 int force_disable_charge = 0;
 static ssize_t force_disable_charge_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	size_t count = 0;
	count += sprintf(buf, "%d\n", force_disable_charge);
	return count;
}
 static ssize_t force_disable_charge_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
	sscanf(buf, "%d ", &force_disable_charge);
	if (force_disable_charge < 0 || force_disable_charge > 1)
		force_disable_charge = 0;
 	return count;
}
 static struct kobj_attribute force_disable_charge_attribute =
__ATTR(force_disable_charge, 0666, force_disable_charge_show, force_disable_charge_store);
 static struct attribute *force_disable_charge_attrs[] = {
	&force_disable_charge_attribute.attr,
	NULL,
};
 static struct attribute_group force_disable_charge_attr_group = {
	.attrs = force_disable_charge_attrs,
};
 static struct kobject *force_disable_charge_kobj;
 int force_disable_charge_init(void)
{
	int ret;
 	force_disable_charge_kobj = kobject_create_and_add("disable_charge", kernel_kobj);
	if (!force_disable_charge_kobj) {
			return -ENOMEM;
	}
 	ret = sysfs_create_group(force_disable_charge_kobj, &force_disable_charge_attr_group);
 	if (ret)
		kobject_put(force_disable_charge_kobj);
 	return ret;
}
 module_init(force_disable_charge_init);

