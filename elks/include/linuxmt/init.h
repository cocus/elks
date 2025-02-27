#ifndef __LINUXMT_INIT_H
#define __LINUXMT_INIT_H

/* Assorted initializers */

#include <linuxmt/types.h>

#if defined(CONFIG_FARTEXT_KERNEL) && !defined(__STRICT_ANSI__)
#define INITPROC __far __attribute__ ((far_section, noinline, section (".fartext.init")))
#else
#define INITPROC
#endif

struct task_struct;
struct gendisk;
struct drive_infot;

/* kernel init routines*/
extern void INITPROC kernel_init(void);
extern int  INITPROC buffer_init(void);
extern void console_init(void);
extern void INITPROC fs_init(void);
extern void INITPROC inode_init(void);
extern void INITPROC irq_init(void);
extern void save_timer_irq(void);
extern void INITPROC mm_init(seg_t,seg_t);
extern void INITPROC seg_add(seg_t start, seg_t end);
extern void INITPROC sched_init(void);
extern void INITPROC serial_init(void);
extern void INITPROC rs_setbaud(dev_t dev, unsigned long baud);
extern void INITPROC sock_init(void);
extern void INITPROC tty_init(void);

extern void INITPROC device_init(void);
extern void INITPROC setup_dev(register struct gendisk *);

extern void tz_init(const char *tzstr);

/* block device init routines*/
extern void INITPROC blk_dev_init(void);
extern int INITPROC bioshd_init(void);
extern int INITPROC get_ide_data(int, struct drive_infot *);
extern int directhd_init(void);
extern void floppy_init(void);
extern void rd_init(void);
extern void ssd_init(void);
extern void romflash_init(void);

/* char device init routines*/
extern void chr_dev_init(void);
extern void cgatext_init(void);
extern void eth_init(void);
extern void ne2k_drv_init(void);
extern void el3_drv_init(void);
extern void wd_drv_init(void);
extern void lp_init(void);
extern void mem_dev_init(void);
extern void meta_init(void);
extern void pty_init(void);
extern void tcpdev_init(void);

extern void kfork_proc(void (*addr)());
extern void arch_setup_user_stack(struct task_struct *, word_t entry);

#endif
