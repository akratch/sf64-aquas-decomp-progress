//  unclear how to use the 4 indices
// loop at 465 unrolls incorrectly
// sp100 shouldn't be on the stack

void Aquas_AqBacoon_Update(AqBacoon* this) {
    s32 i;
    s32 i2;
    s32 i3;
    s32 i7;
    Actor* actor;
    f32 sp110;
    f32 var_fs3;
    f32 var_fs0;
    f32 sp104;
    f32 sp100;
    f32 spFC;
    f32 spF8;
    f32 spF4;
    f32 spF0;
    f32 spEC;
    f32 spE8;
    f32 spE4;
    f32 spE0;
    Vec3f spD4;
    f32 temp3;
    f32 var_fs1;
    gBossFrameCount++;
    
    switch (this->state) {
        case 0:
            if (this->swork[AQ_SWK_21] == 0) {
                for (i2 = 0, actor = &gActors[0]; i2 < 3; actor++) {
                    if (actor->obj.status == OBJ_FREE) {
                        Actor_Initialize(actor);
                        actor->obj.status = OBJ_INIT;
                        actor->obj.id = OBJ_ACTOR_AQ_BACOON_BARNACLE;
                        actor->iwork[0] = i2;
                        Object_SetInfo(&actor->info, actor->obj.id);
                        i2++;
                    }
                }

                this->swork[AQ_SWK_21] = 1;
                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 40);
                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 40);
                Radio_PlayMessage(gMsg_ID_15100, RCID_FOX);
            }
            if (fabsf(this->obj.pos.z - gPlayer[0].trueZpos) <= 3000.0f) {
                D_i3_801C4190[6] = 1;
                this->timer_056 = 20;
                Audio_PlaySequence(SEQ_PLAYER_BGM, NA_BGM_BOSS_AQ, 0, 1);
                this->state = 1;
            }
            break;

        case 1:
            if (this->timer_056 == 0) {
                D_i3_801C4308[14] = 80.0f;
                D_i3_801C4308[12] = (D_i3_801C4308[13] = 0.0f);
                this->timer_056 = 20;
                this->state = 2;
                AUDIO_PLAY_SFX(NA_SE_BUBBLE_UP, this->sfxSource, 0);
            }
            break;

        case 2:
            Aquas_801B0FCC(this);
            if (!(this->timer_056 & 1)) {
                for (i2 = 0; i2 < 30; i2++) {
                    Aquas_Bubble_Spawn(
                        gBosses[0].obj.pos.x + RAND_FLOAT_CENTERED(1800.0f),
                        gBosses[0].obj.pos.y + RAND_FLOAT_CENTERED(500.0f),
                        (gBosses[0].obj.pos.z + 700.0f) + RAND_FLOAT_CENTERED(1000.0f), 7.0f, 2
                    );
                }
            }
            if (this->timer_056 == 0) {
                this->timer_056 = 40;
                this->state = 3;
            }
            break;

        case 3:
            Aquas_801B0FCC(this);
            Math_SmoothStepToF(&D_i3_801C4308[12], -45.0f, 0.5f, 1.0f, 0.01f);
            Math_SmoothStepToF(&D_i3_801C4308[13], 30.0f, 0.5f, 1.0f, 0.01f);
            Math_SmoothStepToAngle(&D_i3_801C4308[14], 0.0f, 1.0f, 2.0f, 0.0f);
            Math_SmoothStepToAngle(&D_i3_801C4308[15], D_i3_801C0190[this->swork[AQ_SWK_20]], 1.0f, 10, 0.0f);
            if (this->timer_056 == 0) {
                this->timer_056 = 10;
                this->swork[AQ_SWK_20]++;
                if (this->swork[AQ_SWK_20] >= 5) {
                    this->state = 4;
                }
            }
            break;

        case 4:
            Aquas_801B0FCC(this);
            Math_SmoothStepToF(&D_i3_801C4308[58], 0.25f, 0.3f, 1.0f, 0.0f);
            if (this->timer_056 == 0) {
                this->timer_056 = 20;
                this->state = 5;
            }
            break;

        case 5:
            Aquas_801B0FCC(this);
            Math_SmoothStepToF(&D_i3_801C4308[58], 0.25f, 0.3f, 1.0f, 0.0f);
            if (this->timer_056 == 0) {
                this->timer_056 = 30;
                this->state = 6;
            }
            break;

        case 6:
            Aquas_801B0FCC(this);
            if (this->timer_056 == 0) {
                this->state = 7;
            }
            break;

        case 7:
            this->swork[AQ_SWK_19] = 500;
            D_i3_801C4308[79] = -28.0f;
            Math_SmoothStepToF(&D_i3_801C4308[54], 1.0f, 0.001f, 0.01f, 0.0f);
            Math_SmoothStepToF(&D_i3_801C4308[61], 1.0f, 0.001f, 0.01f, 0.0f);
            if (D_i3_801C4308[54] >= 0.9f) {
                this->timer_056 = 20;
                D_i3_801C4308[79] = 0.0f;
                this->swork[AQ_SWK_0] = 3;
                this->state = 8;
            }
            break;

        case 8:
            if (this->timer_056 == 0) {
                this->timer_056 = 20;
                this->swork[AQ_SWK_12] = 10;
                D_i3_801C42A0[3] = 0;
                Radio_PlayMessage(gMsg_ID_2225, RCID_SLIPPY);
                this->swork[AQ_SWK_26] = gBossFrameCount + 156;
                this->state = 9;
            }
            break;

        case 9:
            if (this->timer_056 == 0) {
                this->state = 10;
            }
            break;

        case 10:

        case 11:

        case 12:
            Aquas_801B1008(this, 500);
            break;

        case 13:
            Aquas_801B1008(this, 60);
            break;

        case 14:
            if (this->timer_056 == 58) {
                AUDIO_PLAY_SFX(NA_SE_EN_SHELL_FILLOPEN, this->sfxSource, 4);
            }
            if ((this->timer_056 == 0) && (D_i3_801C4308[12] <= (-44.0f))) {
                this->swork[AQ_SWK_2] = (this->swork[AQ_SWK_3] = 20);
                this->state = 15;
            }
            if (this->timer_056 == 40) {
                Radio_PlayMessage(gMsg_ID_15140, RCID_PEPPY);
            }
            break;

        case 15:
            if (this->swork[AQ_SWK_2] == 0) {
                this->swork[AQ_SWK_2] = 100 + RAND_INT(50.0f);
            }
            if (this->swork[AQ_SWK_3] == 0) {
                this->swork[AQ_SWK_3] = 100 + RAND_INT(50.0f);
            }
            break;

        case 16:
            D_ctx_801779A8[0] = 20.0f;
            if (gCameraShake == 0) {
                gFillScreenAlpha =
                    (gFillScreenRed = (gFillScreenGreen = (gFillScreenBlue = (gFillScreenAlphaTarget = 255))));
                gFillScreenAlphaTarget = 0;
                gFillScreenAlphaStep = 25;
                gCameraShake = 20 + RAND_FLOAT(20);
            }
            if (gCameraShake == 29) {
                gFillScreenRed = (gFillScreenGreen = (gFillScreenBlue = (gFillScreenAlpha = 0)));
            }
            Math_SmoothStepToF(&D_i3_801C41B8[25], gSurfaceWaterYPos, 1.0f, 100, 0.f);
            Math_SmoothStepToF(&D_i3_801C41B8[26], 128.0f, 1.0f, 100, 0.f);
            for (i3 = 0; i3 < AQ_LIMB_MAX; i3++) {
                if (sAqBacoonlimbTimers[i3] == 0) {
                    sAqBacoonlimbTimers[i3] = 100;
                }
            }

            if (D_i3_801C42A0[7] == 0) {
                D_i3_801C42A0[1] =
                    (D_i3_801C42A0[2] =
                         (D_i3_801C42A0[4] = (D_i3_801C42A0[5] = (D_i3_801C42A0[6] = (D_i3_801C42A0[7] = 50)))));
            }
            if ((gGameFrameCount % 2) == 0) {
                Effect_Effect390_Spawn(
                    this->obj.pos.x + RAND_FLOAT_CENTERED(1200.0f),
                    (this->obj.pos.y + 400.0f) + RAND_FLOAT_CENTERED(400.0f),
                    (this->obj.pos.z + 1000.0f) + RAND_FLOAT_CENTERED(800.0f), this->vel.x, this->vel.y, this->vel.z,
                    0.5f, 10
                );
                Effect_FireSmoke1_Spawn4(
                    this->obj.pos.x + RAND_FLOAT_CENTERED(1200.0f),
                    (this->obj.pos.y + 200.0f) + RAND_FLOAT_CENTERED(400.0f),
                    (this->obj.pos.z + 1000.0f) + RAND_FLOAT_CENTERED(800.0f), 10.0f
                );
            }
            if (i3 && i3) {
            }
            for (i3 = 0; i3 < 3; i3++) {
                func_effect_80081A8C(
                    this->obj.pos.x + RAND_FLOAT_CENTERED(1200.0f),
                    (this->obj.pos.y + 200.0f) + RAND_FLOAT_CENTERED(200.0f),
                    (this->obj.pos.z + 1000.0f) + RAND_FLOAT_CENTERED(800.0f), 3.0f + RAND_FLOAT(3.0f), 5
                );
            }

            if (this->timer_056 == 0) {
                gEffects[98].obj.status = OBJ_FREE;
                gEffects[99].obj.status = OBJ_FREE;
                Effect_EffectBossExplosion_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + 600.0f, 40.0f);
                this->timer_056 = 50;
                for (i3 = 0; i3 < AQ_LIMB_MAX; i3++) {
                    sAqBacoonlimbTimers[i3] = 100;
                }

                gFillScreenRed = (gFillScreenGreen = (gFillScreenBlue = (gFillScreenAlpha = 0)));
                this->state = 17;
            }
            break;

        case 17:
            if (this->timer_056 == 20) {
                gEffects[96].obj.status = OBJ_FREE;
                gEffects[97].obj.status = OBJ_FREE;
                Effect_EffectBossExplosion_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + 600.0f, 80.0f);
            }
            D_i3_801C42A0[0] -= 4;
            if (D_i3_801C42A0[0] < 0) {
                D_i3_801C42A0[0] = 0;
            }
            for (i3 = 0; i3 < 21; i3++) {
                Math_SmoothStepToF(&D_i3_801C4308[52 + i3], 0.1f, 0.1f, 1.0f, 0.0f);
            }

            Math_SmoothStepToF(&this->fwork[AQ_FWK_8], 0.1f, 0.1f, 1.0f, 0.0f);
            Math_SmoothStepToF(&this->fwork[AQ_FWK_9], 0.1f, 0.1f, 1.0f, 0.0f);
            Math_SmoothStepToF(&this->fwork[AQ_FWK_10], 0.1f, 0.1f, 1.0f, 0.0f);
            if ((gGameFrameCount % 2) == 0) {
                Effect_Effect390_Spawn(
                    this->obj.pos.x + RAND_FLOAT_CENTERED(1200.0f),
                    (this->obj.pos.y + 400.0f) + RAND_FLOAT_CENTERED(400.0f),
                    (this->obj.pos.z + 1000.0f) + RAND_FLOAT_CENTERED(800.0f), this->vel.x, this->vel.y, this->vel.z,
                    0.7f, 15
                );
            }
            if (this->timer_056 == 1) {
                for (i3 = 0; i3 < AQ_LIMB_MAX; i3++) {
                    if (i3 != AQ_LIMB_27) {
                        sAqBacoonlimbTimers[i3] = 1000;
                    }
                }
            }
            if (this->timer_056 == 0) {
                this->timer_056 = 300;
                this->state = 18;
            }
            break;

        case 18:
            if (this->timer_056 != 0) {
                for (i3 = 0; i3 < 30; i3++) {
                    Aquas_Bubble_Spawn(
                        gBosses[0].obj.pos.x + RAND_FLOAT_CENTERED(1800.0f),
                        gBosses[0].obj.pos.y + RAND_FLOAT_CENTERED(500.0f),
                        (gBosses[0].obj.pos.z + 700.0f) + RAND_FLOAT_CENTERED(1000.0f), 7.0f, 2
                    );
                }
            }
            break;
    }

    switch (this->swork[AQ_SWK_0]) {
        case 0:
            if (D_i3_801C42A0[23] == 0) {
                D_i3_801C4308[79] = -180.0f;
            } else {
                Math_SmoothStepToF(&D_i3_801C4308[79], 0.0f, 0.05f, 0.2f, 0.0f);
            }
            Math_SmoothStepToF(&D_i3_801C4308[10], D_i3_801C4308[79], 0.05f, 0.3f, 0.0f);
            break;

        case 1:
            Math_SmoothStepToF(&D_i3_801C4308[10], -28.0f, 0.05f, 0.3f, 0.0f);
            if (this->timer_052 < 3) {
                Aquas_801B0F88(this);
            }
            break;

        case 2:
            break;

        case 3:
            Math_SmoothStepToF(&D_i3_801C4308[10], D_i3_801C4308[79], 0.5f, 10.0f, 0.0f);
            if (fabsf(D_i3_801C4308[10]) <= 5.0f) {
                this->swork[AQ_SWK_0] = 0;
                this->timer_052 = 0;
                this->swork[AQ_SWK_19] = 500;
                D_i3_801C4308[79] = 0.0f;
                AUDIO_PLAY_SFX(NA_SE_EN_SHELL_CLOSE, this->sfxSource, 4);
                if (this->state < 14) {
                    for (i3 = 0, actor = &gActors[0]; i3 < ARRAY_COUNT(gActors); i3++, actor++) {
                        if ((actor->obj.id == OBJ_ACTOR_AQ_GAROA) && (actor->obj.status == OBJ_ACTIVE)) {
                            actor->iwork[0] = 1;
                        }
                    }

                    this->timer_058 = 30;
                    this->swork[AQ_SWK_0] = 4;
                    gCameraShake = 50;
                    AUDIO_PLAY_SFX(NA_SE_WATER_PRESSURE, this->sfxSource, 0);
                    Effect_Effect348_Spawn(this->obj.pos.x, this->obj.pos.z + 800.0f, 0, 100.0f);
                    var_fs3 = 80.0f;
                    for (i2 = 0; i2 < 3; i2++, var_fs3 += 10.0f) {
                        for (i3 = 0; i3 < 9; i3++) {
                            var_fs0 = (SIN_DEG((27 + (2 * i3)) * (10.0f + (3 * i2))) * var_fs3) * 10.0f;
                            var_fs1 = (COS_DEG((27 + (2 * i3)) * (10.0f + (3 * i2))) * var_fs3) * 10.0f;
                            temp3 = gGroundHeight + 30.0f;
                            Effect_Effect364_Spawn(
                                this->obj.pos.x + var_fs0, temp3, (this->obj.pos.z + 1000.0f) + var_fs1, 20.0f
                            );
                        }
                    }
                }
            }
            break;

        case 4:
            this->swork[AQ_SWK_19] = 50;
            Math_SmoothStepToF(&D_i3_801C4308[10], D_i3_801C4308[79], 0.5f, 5.0f, 0.0f);
            if (this->timer_058 > 10) {
                Math_SmoothStepToF(D_ctx_801779A8, 20.0f, 1.0f, 5.0f, 0.0f);
            }
            if (this->timer_058 != 0) {
                gPlayer[0].boostCooldown = 1;
                Math_SmoothStepToF(&D_i3_801C41B8[24], 20.0f, 0.1f, 1.0f, 0.0f);
                Math_SmoothStepToF(&gPlayer[0].camDist, 180.0f, 0.4f, 20.0f, 0.0f);
            } else {
                Math_SmoothStepToF(&D_i3_801C41B8[24], 0.0f, 0.01f, 0.1f, 0.0f);
                Math_SmoothStepToF(&gPlayer[0].camDist, 0.0f, 0.1f, 2.0f, 0.0f);
                if (gPlayer[0].camDist < 0.1f) {
                    gPlayer[0].boostCooldown = 0;
                    gPlayer[0].camDist = (D_i3_801C41B8[24] = 0.0f);
                    this->swork[AQ_SWK_0] = 0;
                }
            }
            break;
    }

    Math_SmoothStepToF(&D_i3_801C4308[80], 0.0f, 1.0f, 2.0f, 0);
    Math_SmoothStepToF(&D_i3_801C4308[11], D_i3_801C4308[80], 0.1f, 2.0f, 0);
    if (this->dmgType != DMG_NONE) {
        this->dmgType = DMG_NONE;
        if (fabsf(D_i3_801C4308[10]) >= 5.0f) {
            switch (this->dmgPart) {
                case 13:
                    if ((this->swork[AQ_SWK_12] != 0) && (this->state >= 15)) {
                        if (D_i3_801C42A0[23] == 0) {
                            sAqBacoonlimbTimers[AQ_LIMB_9] = (D_i3_801C42A0[3] = 50);
                            D_i3_801C42A0[22] = 0;
                            this->swork[AQ_SWK_12]--;
                            this->swork[AQ_SWK_13] = 70;
                            AUDIO_PLAY_SFX(NA_SE_EN_EYEFILM_DAMAGE, this->sfxSource, 4);
                        }
                    } else if (this->state >= 10) {
                        AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
                    }
                    break;

                case 14:
                    if (this->damage == 31) {
                        if (D_i3_801C42A0[23] != 0) {
                            AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
                        } else if ((this->state >= 15) && (this->swork[AQ_SWK_8] != 0)) {
                            D_i3_801C42A0[1] = 50;
                            sAqBacoonlimbTimers[AQ_LIMB_7] = 50;
                            this->swork[AQ_SWK_8]--;
                            AUDIO_PLAY_SFX(NA_SE_EN_WT_DAMAGE_S, this->sfxSource, 4);
                            if (this->swork[AQ_SWK_8] == 0) {
                                spD4.x = D_i3_801C4308[73];
                                spD4.y = D_i3_801C4308[74];
                                spD4.z = D_i3_801C4308[75];
                                Effect_TimedSfx_Spawn(&spD4, NA_SE_EN_WT_DISAPPEAR_L);
                                this->swork[AQ_SWK_10] = 250.0f + RAND_FLOAT(50.0f);
                            }
                        }
                    }
                    break;

                case 15:
                    if (this->damage == 31) {
                        if (D_i3_801C42A0[23] != 0) {
                            AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
                        } else if ((this->state >= 15) && (this->swork[AQ_SWK_9] != 0)) {
                            D_i3_801C42A0[2] = 50;
                            sAqBacoonlimbTimers[AQ_LIMB_8] = 50;
                            this->swork[AQ_SWK_9]--;
                            AUDIO_PLAY_SFX(NA_SE_EN_WT_DAMAGE_S, this->sfxSource, 4);
                            if (this->swork[AQ_SWK_9] == 0) {
                                spD4.x = D_i3_801C4308[76];
                                spD4.y = D_i3_801C4308[77];
                                spD4.z = D_i3_801C4308[78];
                                Effect_TimedSfx_Spawn(&spD4, NA_SE_EN_WT_DISAPPEAR_L);
                                this->swork[AQ_SWK_11] = 250.0f + RAND_FLOAT(50.0f);
                            }
                        }
                    }
                    break;

                case 16:
                    if (this->damage == 31) {
                        if (D_i3_801C42A0[23] != 0) {
                            AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
                        } else if (this->state >= 15) {
                            D_i3_801C42A0[4] = 75;
                        }
                    }
                    break;

                case 17:
                    if (this->damage == 31) {
                        if (D_i3_801C42A0[23] != 0) {
                            AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
                        } else if (this->state >= 15) {
                            D_i3_801C42A0[5] = 75;
                        }
                    }
                    break;

                case 18:
                    if (((((this->damage == 31) && (this->swork[AQ_SWK_1] != 2)) && (this->swork[AQ_SWK_12] == 0))
                         && (this->state == 15))
                        && (this->health != 0))
                    {
                        if (D_i3_801C42A0[23] != 0) {
                            AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
                        } else {
                            for (i7 = 0; i7 < AQ_LIMB_MAX; i7 += 4) {
                                i = 50;
                                i2 = 50;
                                i3 = 50;
                                actor = (Actor*) 50;
                                if (i) {}
                                if (i2) {}
                                if (i3) {}
                                if (actor) {}
                                sAqBacoonlimbTimers[i7 + 3] = (s32) actor;
                                sAqBacoonlimbTimers[i7 + 2] = i3;
                                sAqBacoonlimbTimers[i7 + 1] = i2;
                                sAqBacoonlimbTimers[i7 + 0] = i;
                                if (0) {}
                            }

                            D_i3_801C42A0[1] = D_i3_801C42A0[2] = D_i3_801C42A0[4] = D_i3_801C42A0[5] =
                                D_i3_801C42A0[6] = D_i3_801C42A0[7] = 50;
                            this->swork[AQ_SWK_13] = 40;
                            this->swork[AQ_SWK_1] = 2;
                            AUDIO_PLAY_SFX(NA_SE_EN_SHELL_DAMAGE, this->sfxSource, 4);
                            this->health -= this->damage;
                            if ((this->swork[AQ_SWK_25] == 0) || (this->swork[AQ_SWK_25] == 2)) {
                                Radio_PlayMessage(gMsg_ID_7086, RCID_SLIPPY);
                            }
                            this->swork[AQ_SWK_25]++;
                            if (this->health <= 0) {
                                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 40);
                                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 40);
                                Boss_AwardBonus(this);
                                Radio_PlayMessage(gMsg_ID_15252, RCID_SLIPPY);
                                if (this->damage) {}
                                if (this->damage) {}
                                gTeamLowHealthMsgTimer = -1;
                                if ((gPlayer[0].state == PLAYERSTATE_ACTIVE)
                                    || (gPlayer[0].state == PLAYERSTATE_U_TURN))
                                {
                                    gPlayer[0].state = PLAYERSTATE_LEVEL_COMPLETE;
                                    gPlayer[0].csState = 0;
                                }
                                D_i3_801C4190[1] = 0;
                                D_i3_801C4190[5] = 0;
                                D_i3_801C4190[3] = 0;
                                D_i3_801C4190[4] = 0;
                                D_i3_801C4190[0] = 0;
                                this->health = 0;
                                this->swork[AQ_SWK_13] = 40;
                                this->swork[AQ_SWK_1] = 2;
                                this->timer_056 = 50;
                                AUDIO_PLAY_SFX(NA_SE_EN_SHELL_DOWN, this->sfxSource, 4);
                                gShowBossHealth = false;
                                this->state = 16;
                            }
                        }
                    }
                    break;

                case 19:

                case 20:
                    if (this->damage == 31) {
                        if (D_i3_801C42A0[23] != 0) {
                            AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
                        } else if (this->state >= 15) {
                            D_i3_801C42A0[6] = 50;
                        }
                    }
                    break;

                default:
                    AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
                    break;
            }
        }
    }
    if (this->state >= 15) {
        switch (this->swork[AQ_SWK_1]) {
            case 0:
                Math_SmoothStepToF(&D_i3_801C4308[12], -45.0f, 1.0f, this->fwork[AQ_FWK_1], 0.01f);
                Math_SmoothStepToF(&D_i3_801C4308[13], 30.0f, 1.0f, this->fwork[AQ_FWK_1], 0.01f);
                if ((this->timer_050 == 0) && ((*(&D_i3_801C4308[12])) == (-45.0f))) {
                    this->timer_050 = 7;
                    this->swork[AQ_SWK_1]++;
                }
                break;

            case 1:
                sp104 = 2.0f * this->fwork[AQ_FWK_1];
                Math_SmoothStepToF(&D_i3_801C4308[12], 0.0f, 1.0f, sp104, 0.0001f);
                Math_SmoothStepToF(&D_i3_801C4308[13], 0.0f, 1.0f, sp104, 0.0001f);
                if (this->timer_050 == 0) {
                    this->swork[AQ_SWK_1] = 0;
                    this->timer_050 = 40.0f - ((this->health - 150) / 5.0f);
                }
                break;

            case 2:
                if (D_i3_801C42A0[7] != 0) {
                    Math_SmoothStepToF(&D_i3_801C4308[12], -80.0f, 1.0f, 10.0f, 0.0001f);
                    Math_SmoothStepToF(&D_i3_801C4308[13], 30.0f, 1.0f, 10.0f, 0.0001f);
                } else {
                    this->timer_050 = 50;
                    this->swork[AQ_SWK_1] = 0;
                }
                break;
        }
    }
    this->swork[AQ_SWK_14] += D_i3_801C0150[this->swork[AQ_SWK_18]][0];
    this->swork[AQ_SWK_15] += D_i3_801C0150[this->swork[AQ_SWK_18]][1];
    this->swork[AQ_SWK_16] += D_i3_801C0150[this->swork[AQ_SWK_18]][2];
    if (this->swork[AQ_SWK_14] < 0) {
        this->swork[AQ_SWK_14] = 0;
    }
    if (this->swork[AQ_SWK_15] < 0) {
        this->swork[AQ_SWK_15] = 0;
    }
    if (this->swork[AQ_SWK_16] < 0) {
        this->swork[AQ_SWK_16] = 0;
    }
    if (this->swork[AQ_SWK_17] == 0) {
        this->swork[AQ_SWK_17] = 10;
        this->swork[AQ_SWK_18]++;
        this->swork[AQ_SWK_18] &= 3;
    }
    if ((this->state >= 4) && (this->state < 16)) {
        var_fs0 = gPlayer[0].pos.x - this->obj.pos.x;
        sp104 = gPlayer[0].pos.y - this->obj.pos.y;
        spFC = gPlayer[0].trueZpos - this->obj.pos.z;
        spE8 = Math_RadToDeg(Math_Atan2F(var_fs0, spFC));
        spE4 = Math_RadToDeg(-Math_Atan2F(sp104, sqrtf((var_fs0 * var_fs0) + (spFC * spFC))));
        if ((spE8 <= 40.0f) || (spE8 >= 320.0f)) {
            Math_SmoothStepToAngle(&D_i3_801C4308[15], spE8, 1.0f, 5.0f, 0.001f);
        }
        if ((spE4 <= 30.0f) || (spE4 >= 330.0f)) {
            Math_SmoothStepToAngle(&D_i3_801C4308[14], spE4, 1.0f, 5.0f, 0.001f);
        }
    }
    for (i3 = 0; i3 < 6; i3++) {
        if ((D_i3_801C42A0[i3 + 1] == 0) && (this->state < 17)) {
            if (((i3 + 1) != this->swork[AQ_SWK_6]) && ((i3 + 1) != this->swork[AQ_SWK_7])) {
                i7 = D_i3_801C42A0[i3 + 16];
                Math_SmoothStepToF(
                    &D_i3_801C4308[52 + i3], D_i3_801BFC94[(4 * i3) + i7].x, D_i3_801BFE18[(4 * i3) + i7].x,
                    D_i3_801BFF38[(4 * i3) + i7].x, 0.00001f
                );
                Math_SmoothStepToF(
                    &D_i3_801C4308[59 + i3], D_i3_801BFC94[(4 * i3) + i7].y, D_i3_801BFE18[(4 * i3) + i7].y,
                    D_i3_801BFF38[(4 * i3) + i7].y, 0.00001f
                );
                Math_SmoothStepToF(
                    &D_i3_801C4308[66 + i3], D_i3_801BFC94[(4 * i3) + i7].z, D_i3_801BFE18[(4 * i3) + i7].z,
                    D_i3_801BFF38[(4 * i3) + i7].z, 0.00001f
                );
                D_i3_801C42A0[i3 + 10]++;
                if (D_i3_801C42A0[i3 + 10] >= D_i3_801BFDB4[(4 * i3) + i7]) {
                    D_i3_801C42A0[i3 + 16]++;
                    if ((D_i3_801C42A0[i3 + 16] >= 4) || (D_i3_801BFDB4[(4 * i3) + D_i3_801C42A0[i3 + 16]] == 100000)) {
                        D_i3_801C42A0[i3 + 10] = 0;
                        D_i3_801C42A0[i3 + 16] = 0;
                    }
                }
            }
        }
    }

    var_fs0 = gPlayer[0].pos.x - D_i3_801C4308[73];
    spF8 = gPlayer[0].pos.x - D_i3_801C4308[76];
    temp3 = gPlayer[0].pos.y - D_i3_801C4308[74];
    spF4 = gPlayer[0].pos.y - D_i3_801C4308[77];
    spFC = gPlayer[0].trueZpos - D_i3_801C4308[75];
    spF0 = gPlayer[0].trueZpos - D_i3_801C4308[78];
    spE8 = Math_RadToDeg(Math_Atan2F(var_fs0, spFC));
    spE0 = Math_RadToDeg(Math_Atan2F(spF8, spF0));
    spFC = sqrtf((var_fs0 * var_fs0) + (spFC * spFC));
    spF0 = sqrtf((spF8 * spF8) + (spF0 * spF0));
    spE4 = Math_RadToDeg(-Math_Atan2F(temp3, spFC));
    spEC = Math_RadToDeg(-Math_Atan2F(spF4, spF0));
    if ((spE8 <= 15.0f) || (spE8 >= 310.0f)) {
        Math_SmoothStepToAngle(&D_i3_801C4308[18], spE8, 1.0f, 5.0f, 0.001f);
    }
    if ((spE4 <= 12.0f) || (spE4 >= 330.0f)) {
        Math_SmoothStepToAngle(&D_i3_801C4308[16], spE4, 1.0f, 5.0f, 0.001f);
    }
    if ((spE0 <= 20.0f) || (spE0 >= 315.0f)) {
        Math_SmoothStepToAngle(&D_i3_801C4308[19], spE0, 1.0f, 5.0f, 0.001f);
    }
    if ((spEC <= 12.0f) || (spEC >= 330.0f)) {
        Math_SmoothStepToAngle(&D_i3_801C4308[17], spEC, 1.0f, 5.0f, 0.001f);
    }
    if ((((this->swork[AQ_SWK_2] == 1) && (this->swork[AQ_SWK_8] != 0)) && (this->health != 0))
        && (this->swork[AQ_SWK_6] == 0))
    {
        D_i3_801C42A0[10] = (D_i3_801C42A0[16] = 0);
        this->swork[AQ_SWK_6] = 1;
    }
    if ((((this->swork[AQ_SWK_3] == 1) && (this->swork[AQ_SWK_9] != 0)) && (this->health != 0))
        && (this->swork[AQ_SWK_7] == 0))
    {
        D_i3_801C42A0[11] = (D_i3_801C42A0[17] = 0);
        this->swork[AQ_SWK_7] = 2;
    }
    if (this->health != 0) {
        for (i7 = 0; i7 < 2; i7++) {
            if (this->swork[AQ_SWK_6 + i7] != 0) {
                i2 = this->swork[AQ_SWK_4 + i7];
                Math_SmoothStepToF(
                    &D_i3_801C4308[52 + i7], D_i3_801C00B0[0][i2], D_i3_801C00F0[0][i2], D_i3_801C0120[0][i2], 0.00001f
                );
                Math_SmoothStepToF(
                    &D_i3_801C4308[59 + i7], D_i3_801C00B0[1][i2], D_i3_801C00F0[1][i2], D_i3_801C0120[1][i2], 0.00001f
                );
                Math_SmoothStepToF(
                    &D_i3_801C4308[66 + i7], D_i3_801C00B0[2][i2], D_i3_801C00F0[2][i2], D_i3_801C0120[2][i2], 0.00001f
                );
                D_i3_801C42A0[i7 + 10]++;
                if (D_i3_801C42A0[i7 + 10] >= D_i3_801C00E0[i2]) {
                    this->swork[AQ_SWK_4 + i7]++;
                    if (this->swork[AQ_SWK_4 + i7] == 2) {
                        i = 4;
                        if (D_i3_801C42A0[23] == 0) {
                            i = ((160 - this->health) / 10) + 10;
                            if (this->health < 31) {
                                i += 10;
                            }
                            if (i > 40) {
                                i = 40;
                            }
                        }
                        spD4.x = D_i3_801C4308[73 + (3 * i7)];
                        spD4.y = D_i3_801C4308[74 + (3 * i7)];
                        spD4.z = D_i3_801C4308[75 + (3 * i7)];
                        Effect_TimedSfx_Spawn(&spD4, NA_SE_EN_P_BALL_SHOT);
                        i2 = 0;
                        for (i3 = 0; (i2 <= i) && (i3 < ARRAY_COUNT(gActors)); i3++) {
                            if ((gActors[i3].obj.status == OBJ_FREE) && (i3 < ARRAY_COUNT(gActors))) {
                                actor = (Actor*) ((i2 * 4) - i2);
                                Actor_Initialize(&gActors[i3]);
                                gActors[i3].obj.status = OBJ_INIT;
                                gActors[i3].obj.id = OBJ_ACTOR_AQ_PEARL;
                                gActors[i3].obj.pos.x = D_i3_801C4308[73 + (3 * i7)];
                                gActors[i3].obj.pos.y = D_i3_801C4308[74 + (3 * i7)] + 30.0f;
                                gActors[i3].obj.pos.z = D_i3_801C4308[75 + (3 * i7)] + 150.0f;
                                if (Rand_ZeroOne() < 0.5f) {
                                    var_fs1 = Math_ModF(D_i3_801C4308[i7 + 16] + RAND_FLOAT_CENTERED(60.0f), 360.0f);
                                    sp104 = Math_ModF(D_i3_801C4308[i7 + 18] + RAND_FLOAT_CENTERED(60.0f), 360.0f);
                                    if (this->health < 61) {
                                        if (i7 == 0) {
                                            var_fs1 =
                                                Math_ModF(D_i3_801C4308[i7 + 16] + RAND_FLOAT_CENTERED(30.0f), 360.0f);
                                            sp104 = Math_ModF(
                                                (D_i3_801C4308[i7 + 18] - 30.0f) + RAND_FLOAT_CENTERED(20.0f), 360.0f
                                            );
                                        } else {
                                            var_fs1 =
                                                Math_ModF(D_i3_801C4308[i7 + 16] + RAND_FLOAT_CENTERED(30.0f), 360.0f);
                                            sp104 = Math_ModF(
                                                (D_i3_801C4308[i7 + 18] + 30.0f) + RAND_FLOAT_CENTERED(20.0f), 360.0f
                                            );
                                        }
                                    }
                                } else {
                                    var_fs1 = Math_ModF(D_i3_801C4308[i7 + 16] + RAND_FLOAT_CENTERED(30.0f), 360.0f);
                                    sp104 = Math_ModF(D_i3_801C4308[i7 + 18] + RAND_FLOAT_CENTERED(30.0f), 360.0f);
                                }
                                gActors[i3].fwork[3] = var_fs1;
                                gActors[i3].fwork[4] = sp104;
                                gActors[i3].timer_0BC = (s32) actor;
                                gActors[i3].fwork[1] = D_i3_801C4308[i7 + 16];
                                gActors[i3].fwork[2] = D_i3_801C4308[i7 + 18];
                                Object_SetInfo(&gActors[i3].info, gActors[i3].obj.id);
                                if (i3 >= ARRAY_COUNT(gActors)) {
                                    gActors[i3].obj.status = OBJ_FREE;
                                }
                                i2++;
                            }
                        }
                    }
                    if (this->swork[AQ_SWK_4 + i7] >= 4) {
                        D_i3_801C42A0[10 + i7] = (this->swork[AQ_SWK_6 + i7] = (this->swork[AQ_SWK_4 + i7] = 0));
                    }
                }
            }
        }
    }
    i = 26;
    while (i < 107) {
        var_fs0 = D_i3_801C4308[10] - 10;
        if (fabsf(D_i3_801C4308[10]) <= 5.0f) {
            var_fs0 = 0.0f;
        }
        this->info.hitbox[i] = var_fs0;
        i += 5;
        i += 5;
    }

    if (this->state >= 10) {
        sp110 = D_i3_801C42A0[9];
        i2 = gGameFrameCount & 0x1F;
        if (sAqBacoonlimbTimers[AQ_LIMB_9] != 0) {
            Math_SmoothStepToF(&sp110, 255.0f, 1.0f, 10, 0.0001f);
        } else if ((i2 & 0x10) == 0) {
            Math_SmoothStepToF(&sp110, D_i3_801C005C, 1.0f, 10, 0.0001f);
        } else {
            Math_SmoothStepToF(&sp110, D_i3_801C0058, 1.0f, 10, 0.0001f);
        }
        D_i3_801C42A0[9] = sp110;
    }
    if (D_i3_801C42A0[7] != 0) {
        Math_SmoothStepToF(&D_ctx_801779A8[0], 20.0f, 1.0f, 5.0f, 0);
    }
    for (i2 = 45, i3 = 1, i7 = 0; i7 < 14; i3++, i2++, i7 += 2) {
        if (D_i3_801C42A0[i3] != 0) {
            D_i3_801C4308[i2] = SIN_DEG(D_i3_801C0060[i7 + 0] * D_i3_801C42A0[i3])
                * Aquas_801A958C(D_i3_801C42A0[i3], D_i3_801C0060[i7 + 1]);
            D_i3_801C42A0[i3]--;
        }
    }

    if (this->swork[AQ_SWK_12] != 0) {
        if (D_i3_801C42A0[3] != 0) {
            var_fs3 = 1.0f;
            if (D_i3_801C42A0[22] < 4) {
                var_fs3 = 1.2f;
            }
            Math_SmoothStepToF(&D_i3_801C4308[54], var_fs3, 0.3f, 1.0f, 0.0f);
            Math_SmoothStepToF(&D_i3_801C4308[61], var_fs3, 0.3f, 1.0f, 0.0f);
            D_i3_801C42A0[22]++;
            if (D_i3_801C42A0[22] >= 9) {
                D_i3_801C42A0[22] = 0;
            }
        }
    } else {
        D_i3_801C42A0[3] = 10;
        if (this->swork[AQ_SWK_13] != 0) {
            Math_SmoothStepToF(&D_i3_801C4308[54], 0.0f, 0.3f, 0.5f, 0.0f);
            Math_SmoothStepToF(&D_i3_801C4308[61], 0.0f, 0.3f, 0.5f, 0.0f);
            this->info.hitbox[119] = -10000.0f;
            if (this->swork[AQ_SWK_13] == 1) {
                AUDIO_PLAY_SFX(NA_SE_EN_EYEFILM_REVIVAL, this->sfxSource, 4);
            }
        } else if ((this->health != 0) || (this->state < 16)) {
            Math_SmoothStepToF(&D_i3_801C4308[54], 1.0f, 0.3f, 0.5f, 0.0f);
            Math_SmoothStepToF(&D_i3_801C4308[61], 1.0f, 0.3f, 0.5f, 0.0f);
            if (D_i3_801C4308[61] >= 0.9f) {
                this->swork[AQ_SWK_12] = 10;
                this->info.hitbox[119] = 1028.0f;
            }
        } else {
            Math_SmoothStepToF(&D_i3_801C4308[54], 0, 0.1f, 10, 0);
            Math_SmoothStepToF(&D_i3_801C4308[61], 0, 0.1f, 10.0f, 0);
            D_i3_801C42A0[9] -= 5;
            if (D_i3_801C42A0[9] < 0) {
                D_i3_801C42A0[9] = 0;
            }
        }
    }
    if ((D_i3_801C42A0[7] != 0) || (this->state >= 16)) {
        var_fs3 = 0.25f;
    } else {
        var_fs3 = 1.0f;
    }
    Math_SmoothStepToF(&D_i3_801C4308[58], var_fs3, 0.3f, 1.0f, 0);
    for (i3 = 0; i3 < 2; i3++) {
        if (this->swork[AQ_SWK_8 + i3] == 0) {
            if (this->swork[AQ_SWK_10 + i3] == 1) {
                spD4.x = D_i3_801C4308[73 + (3 * i3)];
                spD4.y = D_i3_801C4308[74 + (3 * i3)];
                spD4.z = D_i3_801C4308[75 + (3 * i3)];
                Effect_TimedSfx_Spawn(&spD4, NA_SE_EN_P_GUN_APPEAR);
            }
            if ((fabsf(D_i3_801C4308[10]) <= 3.0f) || (this->swork[AQ_SWK_10 + i3] == 0)) {
                Math_SmoothStepToF(&D_i3_801C4308[52 + i3], 1.0f, 0.1f, 0.5f, 0.0f);
                Math_SmoothStepToF(&D_i3_801C4308[59 + i3], 1.0f, 0.1f, 0.5f, 0.0f);
                Math_SmoothStepToF(&D_i3_801C4308[66 + i3], 1.0f, 0.1f, 0.5f, 0.0f);
                if (D_i3_801C4308[i3 + 66] >= 0.9f) {
                    for (i2 = 0; i2 < 3; i2++) {
                        spD4.x = D_i3_801C4308[73 + (3 * i3)] + RAND_FLOAT(i2 * 200.0f);
                        spD4.y = D_i3_801C4308[74 + (3 * i3)] + RAND_FLOAT(i2 * 200.0f);
                        spD4.z = D_i3_801C4308[75 + (3 * i3)] + RAND_FLOAT(i2 * 400.0f);
                        Aquas_SpawnItem(&spD4, OBJ_ITEM_SILVER_RING);
                    }

                    this->swork[AQ_SWK_8 + i3] = 2;
                }
            } else {
                Math_SmoothStepToF(&D_i3_801C4308[52 + i3], 0, 0.1f, 0.5f, 0.0f);
                Math_SmoothStepToF(&D_i3_801C4308[59 + i3], 0, 0.1f, 0.5f, 0.0f);
                Math_SmoothStepToF(&D_i3_801C4308[66 + i3], 0, 0.1f, 0.5f, 0.0f);
                D_i3_801C42A0[i3 + 1] = 50;
            }
        }
    }

    if (this->swork[AQ_SWK_2] != 0) {
        this->swork[AQ_SWK_2]--;
    }
    if (this->swork[AQ_SWK_3] != 0) {
        this->swork[AQ_SWK_3]--;
    }
    if (this->swork[AQ_SWK_10] != 0) {
        this->swork[AQ_SWK_10]--;
    }
    if (this->swork[AQ_SWK_11] != 0) {
        this->swork[AQ_SWK_11]--;
    }
    if (this->swork[AQ_SWK_13] != 0) {
        this->swork[AQ_SWK_13]--;
    }
    if (this->swork[AQ_SWK_17] != 0) {
        this->swork[AQ_SWK_17]--;
    }
    if (this->swork[AQ_SWK_19] != 0) {
        this->swork[AQ_SWK_19]--;
    }
    if (this->swork[AQ_SWK_26] == gBossFrameCount) {
        gShowBossHealth = true;
    }
    if (this->swork[AQ_SWK_26] < gBossFrameCount) {
        gBossHealthBar = (this->health / 150.0f) * 255.0f;
    }
}
