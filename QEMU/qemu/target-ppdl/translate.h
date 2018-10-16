/*
 * PPDL translation
 *
 * Copyright (c) 2014 Perov Maxim <coder@frtk.ru>
 *
 * [TODO] Add some description
 */

#ifndef TARGET_PPDL_TRANSLATE_H
#define TARGET_PPDL_TRANSLATE_H

void ppdl_translate_init(void);

typedef struct DisasContext {
    TranslationBlock *tb;
    target_ulong pc, ppc, npc;
    uint32_t tb_flags, synced_flags, flags;
    uint32_t is_jmp;
    uint32_t mem_idx;
    int singlestep_enabled;
    uint32_t delayed_branch;
} DisasContext;

#endif // TARGET_PPDL_TRANSLATE_H
