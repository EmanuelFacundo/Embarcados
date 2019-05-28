/**
 * \file  hw_ehrpwm.h
 *
 * \brief EHRPWM register definitions
 */

/*
* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
*/
/*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


#ifndef _HW_EHRPWM_H_
#define _HW_EHRPWM_H_

#ifdef __cplusplus
extern "C" {
#endif

#define EHRPWM_TBCTL		(0x0)
#define EHRPWM_TBSTS		(0x2)
#define EHRPWM_TBPHSHR		(0x4)
#define EHRPWM_TBPHS		(0x6)
#define EHRPWM_TBCTR		(0x8)
#define EHRPWM_TBPRD		(0xA)
#define EHRPWM_CMPCTL		(0xE)
#define EHRPWM_CMPAHR		(0x10)
#define EHRPWM_CMPA		(0x12)
#define EHRPWM_CMPB		(0x14)
#define EHRPWM_AQCTLA		(0x16)
#define EHRPWM_AQCTLB		(0x18)
#define EHRPWM_AQSFRC		(0x1A)
#define EHRPWM_AQCSFRC		(0x1C)
#define EHRPWM_DBCTL		(0x1E)
#define EHRPWM_DBRED		(0x20)
#define EHRPWM_DBFED		(0x22)
#define EHRPWM_TZSEL		(0x24)
#define EHRPWM_TZCTL		(0x28)
#define EHRPWM_TZEINT		(0x2A)
#define EHRPWM_TZFLG		(0x2C)
#define EHRPWM_TZCLR		(0x2E)
#define EHRPWM_TZFRC		(0x30)
#define EHRPWM_ETSEL		(0x32)
#define EHRPWM_ETPS		(0x34)
#define EHRPWM_ETFLG		(0x36)
#define EHRPWM_ETCLR		(0x38)
#define EHRPWM_ETFRC		(0x3A)
#define EHRPWM_PCCTL		(0x3C)

/*
** The macro defined below corresponds to HRCTL register of EHRPWM module.
** This definition is used to keep compatibility with the driver(EHRPWM DAL). 
*/
#define EHRPWM_HRCNFG           (0x40)


/**************************************************************************\
* Field Definition Macros
\**************************************************************************/

/* TBCTL */

#define EHRPWM_TBCTL_FREE_SOFT  (0xC000u)
#define EHRPWM_TBCTL_FREE_SOFT_SHIFT (0x000Eu)

#define EHRPWM_TBCTL_PHSDIR     (0x2000u)
#define EHRPWM_TBCTL_PHSDIR_SHIFT    (0x000Du)
#define EHRPWM_TBCTL_CLKDIV     (0x1C00u)
#define EHRPWM_TBCTL_CLKDIV_SHIFT    (0x000Au)
#define EHRPWM_TBCTL_CLKDIV_DIVBY1   (0x0000u)
#define EHRPWM_TBCTL_CLKDIV_DIVBY2   (0x0001u)
#define EHRPWM_TBCTL_CLKDIV_DIVBY4   (0x0002u)
#define EHRPWM_TBCTL_CLKDIV_DIVBY8   (0x0003u)
#define EHRPWM_TBCTL_CLKDIV_DIVBY16  (0x0004u)
#define EHRPWM_TBCTL_CLKDIV_DIVBY32  (0x0005u)
#define EHRPWM_TBCTL_CLKDIV_DIVBY64  (0x0006u)
#define EHRPWM_TBCTL_CLKDIV_DIVBY128 (0x0007u)
#define EHRPWM_TBCTL_HSPCLKDIV  (0x0380u)
#define EHRPWM_TBCTL_HSPCLKDIV_SHIFT (0x0007u)
#define EHRPWM_TBCTL_HSPCLKDIV_DIVBY1 (0x0000u)
#define EHRPWM_TBCTL_HSPCLKDIV_DIVBY2 (0x0001u)
#define EHRPWM_TBCTL_HSPCLKDIV_DIVBY4 (0x0002u)
#define EHRPWM_TBCTL_HSPCLKDIV_DIVBY6 (0x0003u)
#define EHRPWM_TBCTL_HSPCLKDIV_DIVBY8 (0x0004u)
#define EHRPWM_TBCTL_HSPCLKDIV_DIVBY10 (0x0005u)
#define EHRPWM_TBCTL_HSPCLKDIV_DIVBY12 (0x0006u)
#define EHRPWM_TBCTL_HSPCLKDIV_DIVBY14 (0x0007u)
#define EHRPWM_TBCTL_SWFSYNC    (0x0040u)
#define EHRPWM_TBCTL_SWFSYNC_SHIFT   (0x0006u)
#define EHRPWM_TBCTL_SYNCOSEL   (0x0030u)
#define EHRPWM_TBCTL_SYNCOSEL_SHIFT  (0x0004u)
#define EHRPWM_TBCTL_SYNCOSEL_EPWMXSYNCI (0x0000u)
#define EHRPWM_TBCTL_SYNCOSEL_TBCTRZERO (0x0001u)
#define EHRPWM_TBCTL_SYNCOSEL_TBCTRCMPB (0x0002u)
#define EHRPWM_TBCTL_SYNCOSEL_DISABLE 	(0x0003u)
#define EHRPWM_TBCTL_PRDLD      (0x0008u)
#define EHRPWM_TBCTL_PRDLD_SHIFT     (0x0003u)
#define EHRPWM_TBCTL_PHSEN      (0x0004u)
#define EHRPWM_TBCTL_PHSEN_SHIFT     (0x0002u)
#define EHRPWM_TBCTL_CTRMODE    (0x0003u)
#define EHRPWM_TBCTL_CTRMODE_SHIFT   (0x0000u)
#define EHRPWM_TBCTL_CTRMODE_UP      (0x0000u)
#define EHRPWM_TBCTL_CTRMODE_DOWN    (0x0001u)
#define EHRPWM_TBCTL_CTRMODE_UPDOWN  (0x0002u)
#define EHRPWM_TBCTL_CTRMODE_STOPFREEZE (0x0003u)


/* TBSTS */

#define EHRPWM_TBSTS_CTRMAX     (0x0004u)
#define EHRPWM_TBSTS_CTRMAX_SHIFT    (0x0002u)
#define EHRPWM_TBSTS_SYNCI      (0x0002u)
#define EHRPWM_TBSTS_SYNCI_SHIFT     (0x0001u)
#define EHRPWM_TBSTS_CTRDIR     (0x0001u)
#define EHRPWM_TBSTS_CTRDIR_SHIFT    (0x0000u)

/* TBPHSHR */

#define EHRPWM_TBPHSHR_TBPHSHR  (0xFF00u)
#define EHRPWM_TBPHSHR_TBPHSHR_SHIFT (0x0008u)

/* TBPHS */

#define EHRPWM_TBPHS_TBPHS      (0xFFFFu)
#define EHRPWM_TBPHS_TBPHS_SHIFT     (0x0000u)


/* TBCTR */

#define EHRPWM_TBCTR_TBCTR      (0xFFFFu)
#define EHRPWM_TBCTR_TBCTR_SHIFT     (0x0000u)


/* TBPRD */

#define EHRPWM_TBPRD_TBPRD      (0xFFFFu)
#define EHRPWM_TBPRD_TBPRD_SHIFT     (0x0000u)


/* CMPCTL */

#define EHRPWM_CMPCTL_SHDWBFULL (0x0200u)
#define EHRPWM_CMPCTL_SHDWBFULL_SHIFT (0x0009u)
#define EHRPWM_CMPCTL_SHDWAFULL (0x0100u)
#define EHRPWM_CMPCTL_SHDWAFULL_SHIFT (0x0008u)
#define EHRPWM_CMPCTL_SHDWBMODE (0x0040u)
#define EHRPWM_CMPCTL_SHDWBMODE_SHIFT (0x0006u)
#define EHRPWM_CMPCTL_SHDWAMODE (0x0010u)
#define EHRPWM_CMPCTL_SHDWAMODE_SHIFT (0x0004u)
#define EHRPWM_CMPCTL_LOADBMODE (0x000Cu)
#define EHRPWM_CMPCTL_LOADBMODE_SHIFT (0x0002u)
#define EHRPWM_CMPCTL_LOADBMODE_TBCTRZERO (0x0000u)
#define EHRPWM_CMPCTL_LOADBMODE_TBCTRPRD (0x0001u)
#define EHRPWM_CMPCTL_LOADBMODE_ZEROORPRD (0x0002u)
#define EHRPWM_CMPCTL_LOADBMODE_FREEZE (0x0003u)
#define EHRPWM_CMPCTL_LOADAMODE (0x0003u)
#define EHRPWM_CMPCTL_LOADAMODE_SHIFT (0x0000u)
#define EHRPWM_CMPCTL_LOADAMODE_TBCTRZERO (0x0000u)
#define EHRPWM_CMPCTL_LOADAMODE_TBCTRPRD (0x0001u)
#define EHRPWM_CMPCTL_LOADAMODE_ZEROORPRD (0x0002u)
#define EHRPWM_CMPCTL_LOADAMODE_FREEZE (0x0003u)


/* CMPAHR */

#define EHRPWM_CMPAHR_CMPAHR    (0xFF00u)
#define EHRPWM_CMPAHR_CMPAHR_SHIFT   (0x0008u)


/* CMPA */

#define EHRPWM_CMPA_CMPA        (0xFFFFu)
#define EHRPWM_CMPA_CMPA_SHIFT       (0x0000u)


/* CMPB */

#define EHRPWM_CMPB_CMPB        (0xFFFFu)
#define EHRPWM_CMPB_CMPB_SHIFT       (0x0000u)


/* AQCTLA */

#define EHRPWM_AQCTLA_CBD       (0x0C00u)
#define EHRPWM_AQCTLA_CBD_SHIFT      (0x000Au)
#define EHRPWM_AQCTLA_CBD_DONOTHING  (0x0000u)
#define EHRPWM_AQCTLA_CBD_EPWMXALOW  (0x0001u)
#define EHRPWM_AQCTLA_CBD_EPWMXAHIGH (0x0002u)
#define EHRPWM_AQCTLA_CBD_EPWMXATOGGLE (0x0003u)

#define EHRPWM_AQCTLA_CBU       (0x0300u)
#define EHRPWM_AQCTLA_CBU_SHIFT      (0x0008u)
#define EHRPWM_AQCTLA_CBU_DONOTHING  (0x0000u)
#define EHRPWM_AQCTLA_CBU_EPWMXALOW  (0x0001u)
#define EHRPWM_AQCTLA_CBU_EPWMXAHIGH (0x0002u)
#define EHRPWM_AQCTLA_CBU_EPWMXATOGGLE (0x0003u)

#define EHRPWM_AQCTLA_CAD       (0x00C0u)
#define EHRPWM_AQCTLA_CAD_SHIFT      (0x0006u)
#define EHRPWM_AQCTLA_CAD_DONOTHING  (0x0000u)
#define EHRPWM_AQCTLA_CAD_EPWMXALOW  (0x0001u)
#define EHRPWM_AQCTLA_CAD_EPWMXAHIGH (0x0002u)
#define EHRPWM_AQCTLA_CAD_EPWMXATOGGLE (0x0003u)

#define EHRPWM_AQCTLA_CAU       (0x0030u)
#define EHRPWM_AQCTLA_CAU_SHIFT      (0x0004u)
#define EHRPWM_AQCTLA_CAU_DONOTHING  (0x0000u)
#define EHRPWM_AQCTLA_CAU_EPWMXALOW  (0x0001u)
#define EHRPWM_AQCTLA_CAU_EPWMXAHIGH (0x0002u)
#define EHRPWM_AQCTLA_CAU_EPWMXATOGGLE (0x0003u)

#define EHRPWM_AQCTLA_PRD       (0x000Cu)
#define EHRPWM_AQCTLA_PRD_SHIFT      (0x0002u)
#define EHRPWM_AQCTLA_PRD_DONOTHING  (0x0000u)
#define EHRPWM_AQCTLA_PRD_EPWMXALOW  (0x0001u)
#define EHRPWM_AQCTLA_PRD_EPWMXAHIGH (0x0002u)
#define EHRPWM_AQCTLA_PRD_EPWMXATOGGLE (0x0003u)

#define EHRPWM_AQCTLA_ZRO       (0x0003u)
#define EHRPWM_AQCTLA_ZRO_SHIFT      (0x0000u)
#define EHRPWM_AQCTLA_ZRO_DONOTHING  (0x0000u)
#define EHRPWM_AQCTLA_ZRO_EPWMXALOW  (0x0001u)
#define EHRPWM_AQCTLA_ZRO_EPWMXAHIGH (0x0002u)
#define EHRPWM_AQCTLA_ZRO_EPWMXATOGGLE (0x0003u)


/* AQCTLB */

#define EHRPWM_AQCTLB_CBD       (0x0C00u)
#define EHRPWM_AQCTLB_CBD_SHIFT      (0x000Au)
#define EHRPWM_AQCTLB_CBD_DONOTHING  (0x0000u)
#define EHRPWM_AQCTLB_CBD_EPWMXBLOW  (0x0001u)
#define EHRPWM_AQCTLB_CBD_EPWMXBHIGH (0x0002u)
#define EHRPWM_AQCTLB_CBD_EPWMXBTOGGLE (0x0003u)

#define EHRPWM_AQCTLB_CBU       (0x0300u)
#define EHRPWM_AQCTLB_CBU_SHIFT      (0x0008u)
#define EHRPWM_AQCTLB_CBU_DONOTHING  (0x0000u)
#define EHRPWM_AQCTLB_CBU_EPWMXBLOW  (0x0001u)
#define EHRPWM_AQCTLB_CBU_EPWMXBHIGH (0x0002u)
#define EHRPWM_AQCTLB_CBU_EPWMXBTOGGLE (0x0003u)

#define EHRPWM_AQCTLB_CAD       (0x00C0u)
#define EHRPWM_AQCTLB_CAD_SHIFT      (0x0006u)
#define EHRPWM_AQCTLB_CAD_DONOTHING  (0x0000u)
#define EHRPWM_AQCTLB_CAD_EPWMXBLOW  (0x0001u)
#define EHRPWM_AQCTLB_CAD_EPWMXBHIGH (0x0002u)
#define EHRPWM_AQCTLB_CAD_EPWMXBTOGGLE (0x0003u)

#define EHRPWM_AQCTLB_CAU       (0x0030u)
#define EHRPWM_AQCTLB_CAU_SHIFT      (0x0004u)
#define EHRPWM_AQCTLB_CAU_DONOTHING  (0x0000u)
#define EHRPWM_AQCTLB_CAU_EPWMXBLOW  (0x0001u)
#define EHRPWM_AQCTLB_CAU_EPWMXBHIGH (0x0002u)
#define EHRPWM_AQCTLB_CAU_EPWMXBTOGGLE (0x0003u)

#define EHRPWM_AQCTLB_PRD       (0x000Cu)
#define EHRPWM_AQCTLB_PRD_SHIFT      (0x0002u)
#define EHRPWM_AQCTLB_PRD_DONOTHING  (0x0000u)
#define EHRPWM_AQCTLB_PRD_EPWMXBLOW  (0x0001u)
#define EHRPWM_AQCTLB_PRD_EPWMXBHIGH (0x0002u)
#define EHRPWM_AQCTLB_PRD_EPWMXBTOGGLE (0x0003u)

#define EHRPWM_AQCTLB_ZRO       (0x0003u)
#define EHRPWM_AQCTLB_ZRO_SHIFT      (0x0000u)
#define EHRPWM_AQCTLB_ZRO_DONOTHING  (0x0000u)
#define EHRPWM_AQCTLB_ZRO_EPWMXBLOW  (0x0001u)
#define EHRPWM_AQCTLB_ZRO_EPWMXBHIGH (0x0002u)
#define EHRPWM_AQCTLB_ZRO_EPWMXBTOGGLE (0x0003u)


/* AQSFRC */

#define EHRPWM_AQSFRC_RLDCSF    (0x00C0u)
#define EHRPWM_AQSFRC_RLDCSF_SHIFT   (0x0006u)
#define EHRPWM_AQSFRC_RLDCSF_EVTCTRZERO (0x0000u)
#define EHRPWM_AQSFRC_RLDCSF_EVTCTRPRD (0x0001u)
#define EHRPWM_AQSFRC_RLDCSF_ZEROORPRD (0x0002u)
#define EHRPWM_AQSFRC_RLDCSF_IMMEDIATE (0x0003u)

#define EHRPWM_AQSFRC_OTSFB     (0x0020u)
#define EHRPWM_AQSFRC_OTSFB_SHIFT    (0x0005u)
#define EHRPWM_AQSFRC_OTSFB_NOEFFECT (0x0000u)
#define EHRPWM_AQSFRC_OTSFB_EVENT    (0x0001u)

#define EHRPWM_AQSFRC_ACTSFB    (0x0018u)
#define EHRPWM_AQSFRC_ACTSFB_SHIFT   (0x0003u)
#define EHRPWM_AQSFRC_ACTSFB_DONOTHING (0x0000u)
#define EHRPWM_AQSFRC_ACTSFB_CLEAR   (0x0001u)
#define EHRPWM_AQSFRC_ACTSFB_SET     (0x0002u)
#define EHRPWM_AQSFRC_ACTSFB_TOGGLE  (0x0003u)

#define EHRPWM_AQSFRC_OTSFA     (0x0004u)
#define EHRPWM_AQSFRC_OTSFA_SHIFT    (0x0002u)
#define EHRPWM_AQSFRC_OTSFA_NOEFFECT (0x0000u)
#define EHRPWM_AQSFRC_OTSFA_EVENT    (0x0001u)

#define EHRPWM_AQSFRC_ACTSFA    (0x0003u)
#define EHRPWM_AQSFRC_ACTSFA_SHIFT   (0x0000u)
#define EHRPWM_AQSFRC_ACTSFA_DONOTHING (0x0000u)
#define EHRPWM_AQSFRC_ACTSFA_CLEAR   (0x0001u)
#define EHRPWM_AQSFRC_ACTSFA_SET     (0x0002u)
#define EHRPWM_AQSFRC_ACTSFA_TOGGLE  (0x0003u)


/* AQCSFRC */

#define EHRPWM_AQCSFRC_CSFB     (0x000Cu)
#define EHRPWM_AQCSFRC_CSFB_SHIFT    (0x0002u)
#define EHRPWM_AQCSFRC_CSFB_LOW      (0x0001u)
#define EHRPWM_AQCSFRC_CSFB_HIGH     (0x0002u)

#define EHRPWM_AQCSFRC_CSFA     (0x0003u)
#define EHRPWM_AQCSFRC_CSFA_SHIFT    (0x0000u)
#define EHRPWM_AQCSFRC_CSFA_LOW      (0x0001u)
#define EHRPWM_AQCSFRC_CSFA_HIGH     (0x0002u)


/* DBCTL */

#define EHRPWM_DBCTL_IN_MODE    (0x0030u)
#define EHRPWM_DBCTL_IN_MODE_SHIFT   (0x0004u)
#define EHRPWM_DBCTL_IN_MODE_AREDAFED (0x0000u)
#define EHRPWM_DBCTL_IN_MODE_BREDAFED (0x0001u)
#define EHRPWM_DBCTL_IN_MODE_AREDBFED (0x0002u)
#define EHRPWM_DBCTL_IN_MODE_BREDBFED (0x0003u)

#define EHRPWM_DBCTL_POLSEL     (0x000Cu)
#define EHRPWM_DBCTL_POLSEL_SHIFT    (0x0002u)
#define EHRPWM_DBCTL_POLSEL_ACTIVEHIGH (0x0000u)
#define EHRPWM_DBCTL_POLSEL_ALC      (0x0001u)
#define EHRPWM_DBCTL_POLSEL_AHC      (0x0002u)
#define EHRPWM_DBCTL_POLSEL_ACTIVELOW (0x0003u)

#define EHRPWM_DBCTL_OUT_MODE   (0x0003u)
#define EHRPWM_DBCTL_OUT_MODE_SHIFT  (0x0000u)
#define EHRPWM_DBCTL_OUT_MODE_BYPASS (0x0000u)
#define EHRPWM_DBCTL_OUT_MODE_NOREDBFED (0x0001u)
#define EHRPWM_DBCTL_OUT_MODE_AREDNOFED (0x0002u)
#define EHRPWM_DBCTL_OUT_MODE_AREDBFED (0x0003u)


/* DBRED */

#define EHRPWM_DBRED_DEL        (0x03FFu)
#define EHRPWM_DBRED_DEL_SHIFT       (0x0000u)


/* DBFED */

#define EHRPWM_DBFED_DEL        (0x03FFu)
#define EHRPWM_DBFED_DEL_SHIFT       (0x0000u)


/* TZSEL */

#define EHRPWM_TZSEL_OSHT1      (0x0100u)
#define EHRPWM_TZSEL_OSHT1_SHIFT     (0x0008u)


#define EHRPWM_TZSEL_CBC1       (0x0001u)
#define EHRPWM_TZSEL_CBC1_SHIFT      (0x0000u)


/* TZCTL */

#define EHRPWM_TZCTL_TZB        (0x000Cu)
#define EHRPWM_TZCTL_TZB_SHIFT       (0x0002u)
#define EHRPWM_TZCTL_TZB_TRISTATE    (0x0000u)
#define EHRPWM_TZCTL_TZB_FORCEHIGH   (0x0001u)
#define EHRPWM_TZCTL_TZB_FORCELOW    (0x0002u)
#define EHRPWM_TZCTL_TZB_DONOTHING   (0x0003u)

#define EHRPWM_TZCTL_TZA        (0x0003u)
#define EHRPWM_TZCTL_TZA_SHIFT       (0x0000u)
#define EHRPWM_TZCTL_TZA_TRISTATE    (0x0000u)
#define EHRPWM_TZCTL_TZA_FORCEHIGH   (0x0001u)
#define EHRPWM_TZCTL_TZA_FORCELOW    (0x0002u)
#define EHRPWM_TZCTL_TZA_DONOTHING   (0x0003u)


/* TZEINT */

#define EHRPWM_TZEINT_OST       (0x0004u)
#define EHRPWM_TZEINT_OST_SHIFT      (0x0002u)

#define EHRPWM_TZEINT_CBC       (0x0002u)
#define EHRPWM_TZEINT_CBC_SHIFT      (0x0001u)



/* TZFLG */

#define EHRPWM_TZFLG_OST        (0x0004u)
#define EHRPWM_TZFLG_OST_SHIFT       (0x0002u)
#define EHRPWM_TZFLG_CBC        (0x0002u)
#define EHRPWM_TZFLG_CBC_SHIFT       (0x0001u)
#define EHRPWM_TZFLG_INT        (0x0001u)
#define EHRPWM_TZFLG_INT_SHIFT       (0x0000u)


/* TZCLR */

#define EHRPWM_TZCLR_OST        (0x0004u)
#define EHRPWM_TZCLR_OST_SHIFT       (0x0002u)
#define EHRPWM_TZCLR_CBC        (0x0002u)
#define EHRPWM_TZCLR_CBC_SHIFT       (0x0001u)
#define EHRPWM_TZCLR_INT        (0x0001u)
#define EHRPWM_TZCLR_INT_SHIFT       (0x0000u)

/* TZFRC */

#define EHRPWM_TZFRC_OST        (0x0004u)
#define EHRPWM_TZFRC_OST_SHIFT       (0x0002u)
#define EHRPWM_TZFRC_CBC        (0x0002u)
#define EHRPWM_TZFRC_CBC_SHIFT       (0x0001u)


/* ETSEL */

#define EHRPWM_ETSEL_INTEN      (0x0008u)
#define EHRPWM_ETSEL_INTEN_SHIFT     (0x0003u)

#define EHRPWM_ETSEL_INTSEL     (0x0007u)
#define EHRPWM_ETSEL_INTSEL_SHIFT    (0x0000u)
#define EHRPWM_ETSEL_INTSEL_TBCTREQUZERO (0x0001u)
#define EHRPWM_ETSEL_INTSEL_TBCTREQUPRD (0x0002u)
#define EHRPWM_ETSEL_INTSEL_TBCTREQUCMPAINC (0x0004u)
#define EHRPWM_ETSEL_INTSEL_TBCTREQUCMPADEC (0x0005u)
#define EHRPWM_ETSEL_INTSEL_TBCTREQUCMPBINC (0x0006u)
#define EHRPWM_ETSEL_INTSEL_TBCTREQUCMPBDEC (0x0007u)


/* ETPS */

#define EHRPWM_ETPS_INTCNT      (0x000Cu)
#define EHRPWM_ETPS_INTCNT_SHIFT     (0x0002u)
#define EHRPWM_ETPS_INTCNT_NOEVENTS  (0x0000u)
#define EHRPWM_ETPS_INTCNT_ONEEVENT  (0x0001u)
#define EHRPWM_ETPS_INTCNT_TWOEVENTS (0x0002u)
#define EHRPWM_ETPS_INTCNT_THREEEVENTS (0x0003u)

#define EHRPWM_ETPS_INTPRD      (0x0003u)
#define EHRPWM_ETPS_INTPRD_SHIFT     (0x0000u)
#define EHRPWM_ETPS_INTPRD_FIRSTEVENT (0x0001u)
#define EHRPWM_ETPS_INTPRD_SECONDEVENT (0x0002u)
#define EHRPWM_ETPS_INTPRD_THIRDEVENT (0x0003u)


/* ETFLG */

#define EHRPWM_ETFLG_INT        (0x0001u)
#define EHRPWM_ETFLG_INT_SHIFT       (0x0000u)

/* ETCLR */

#define EHRPWM_ETCLR_INT        (0x0001u)
#define EHRPWM_ETCLR_INT_SHIFT       (0x0000u)
#define EHRPWM_ETCLR_INT_NOEFFECT    (0x0000u)
#define EHRPWM_ETCLR_INT_CLEAR       (0x0001u)


/* ETFRC */

#define EHRPWM_ETFRC_INT        (0x0001u)
#define EHRPWM_ETFRC_INT_SHIFT       (0x0000u)

/* PCCTL */

#define EHRPWM_PCCTL_CHPDUTY    (0x0700u)
#define EHRPWM_PCCTL_CHPDUTY_SHIFT   (0x0008u)
#define EHRPWM_PCCTL_CHPDUTY_1DIV8   (0x0000u)
#define EHRPWM_PCCTL_CHPDUTY_2DIV8   (0x0001u)
#define EHRPWM_PCCTL_CHPDUTY_3DIV8   (0x0002u)
#define EHRPWM_PCCTL_CHPDUTY_4DIV8   (0x0003u)
#define EHRPWM_PCCTL_CHPDUTY_5DIV8   (0x0004u)
#define EHRPWM_PCCTL_CHPDUTY_6DIV8   (0x0005u)
#define EHRPWM_PCCTL_CHPDUTY_7DIV8   (0x0006u)
#define EHRPWM_PCCTL_CHPDUTY_RESERVED (0x0007u)

#define EHRPWM_PCCTL_CHPFREQ    (0x00E0u)
#define EHRPWM_PCCTL_CHPFREQ_SHIFT   (0x0005u)
#define EHRPWM_PCCTL_CHPFREQ_DIVBY1  (0x0000u)
#define EHRPWM_PCCTL_CHPFREQ_DIVBY2  (0x0001u)
#define EHRPWM_PCCTL_CHPFREQ_DIVBY3  (0x0002u)
#define EHRPWM_PCCTL_CHPFREQ_DIVBY4  (0x0003u)
#define EHRPWM_PCCTL_CHPFREQ_DIVBY5  (0x0004u)
#define EHRPWM_PCCTL_CHPFREQ_DIVBY6  (0x0005u)
#define EHRPWM_PCCTL_CHPFREQ_DIVBY7  (0x0006u)
#define EHRPWM_PCCTL_CHPFREQ_DIVBY8  (0x0007u)

#define EHRPWM_PCCTL_OSHTWTH    (0x001Eu)
#define EHRPWM_PCCTL_OSHTWTH_SHIFT   (0x0001u)

#define EHRPWM_PCCTL_CHPEN      (0x0001u)
#define EHRPWM_PCCTL_CHPEN_SHIFT     (0x0000u)

/* HR */

#define EHRPWM_HR_HRLOAD		(0x0008u)
#define EHRPWM_HR_HRLOAD_SHIFT		(0x0003u)
#define EHRPWM_HR_HRLOAD_CTR_ZERO	(0x0000u)
#define EHRPWM_HR_HRLOAD_CTR_PRD	(0x0008u)

#define EHRPWM_HR_CTLMODE		(0x0004u)
#define EHRPWM_HR_CTLMODE_SHIFT		(0x0002u)
#define EHRPWM_HR_CTLMODE_CMPAHR	(0x0000u)
#define EHRPWM_HR_CTLMODE_TBPHSHR	(0x0004u)

#define EHRPWM_HR_EDGEMODE		(0x0003u)
#define EHRPWM_HR_EDGEMODE_SHIFT	(0x0000u)
#define EHRPWM_HR_EDGEMODE_DISABLE	(0x0000u)
#define EHRPWM_HR_EDGEMODE_RAISING	(0x0001u)
#define EHRPWM_HR_EDGEMODE_FALLING	(0x0002u)
#define EHRPWM_HR_EDGEMODE_BOTH		(0x0003u)


/* REVID */

#define EHRPWM_REVID_REV        (0xFFFFFFFFu)
#define EHRPWM_REVID_REV_SHIFT       (0x00000000u)


#ifdef __cplusplus
}
#endif

#endif
