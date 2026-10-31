#pragma once
/* OnePlus 7T Pro (hotdog, SM8150-AC, project 19801). Values audited against
 * this phone's own live FDT (714,713 bytes, pulled 2026-10-31) and the
 * shim's SDE probe. Same platform as guacamole (OnePlus 7 Pro): identical
 * splash carve-out, panel resolution, GIC, UFS, IMEM, PS_HOLD and TLMM.
 * Differences: touch is Synaptics S3706 (not Samsung S6SY761), project id
 * 19801 (not 18821). Mirrors tools/devices.py. */

#define BOARD_NAME "hotdog"

/* ABL continuous-splash framebuffer: live FDT reserved-memory
 * "cont_splash_region" = <0x0 0x9c000000 0x0 0x02400000> (36 MiB);
 * the SDE pipe reports SSPP_SRC0_ADDR = 0x9c000000 and stride 0x1680
 * (5760 B = 1440 px) on a 1440x3120 panel (Samsung S6E3HC2, DSC cmd mode). */
#define FB_BASE		0x9c000000UL
#define FB_W		1440
#define FB_H		3120
#define FB_STRIDE	(FB_W * 4)

/* GICv3 (live FDT: interrupt-controller@17a00000, redistributor 0x17a60000). */
#define GICD_BASE	0x17a00000UL
#define GICR_BASE	0x17a60000UL
#define GICR_SIZE	0x100000UL
#define GICR_PE_SIZE	0x20000UL
#define VTIMER_INTID	19	/* GIC_PPI 3 numbering */
#define PTIMER_INTID	18

/* IMEM is qcom,msm-imem@146bf000 (live FDT), so restart_reason@65c sits at
 * 0x146bf65c; PS_HOLD is restart@c264000 (live FDT, qcom,pshold). */
#define IMEM_RESTART_REASON	0x146bf65cUL
#define PSHOLD			0x0c264000UL

/* Internal UFS host: ufshc@1d84000 (live FDT, 2 lanes, UFS 3.0 on hotdog). */
#define UFS_BASE		0x01d84000UL

/* Same as guacamole: probing the UFS registers while ABL has the link gated
 * stalls the bus and the watchdog resets the phone. */
#define PROBE_UFS		0

/* Reset-surviving scratch word in the kernel bank (0x180000000 + 0x18000000). */
#define MARK_PA			0x198000000UL

/* TLMM: pinctrl@03000000 (live FDT), pin stride 0x1000, ctl at +0, io at +4. */
#define BOARD_TLMM_PA		0x03000000UL

/* GPUCC: qcom,gpucc-sm8150 @ 0x2c90000 (same on hotdog). */
#define BOARD_GPUCC_PA		0x02c90000UL
