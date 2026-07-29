# Aquas matching postmortem

## Exact result

- Upstream match: `sf64` commit `ddd75e11d28a0473872d1fd093eed345300b5ba2`
- Function: `Aquas_AqBacoon_Update`
- Compiler: IDO 5.3, `-O2`
- Verified locally against `expected/build/src/overlays/ovl_i3/fox_aq.o`
- Result: 3032/3032 instructions, frame size 296, zero normalized,
  opcode, register, floating-point register, relocation, or word mismatches

The 48 raw words reported by the comparator are linked-address differences
which normalize to zero.

## What the near-match taught us

The final two opcode mismatches in the best experimental sketch appeared in
the case-18 timer initialization loop. The sketch used a forced four-at-a-time
loop and several fake scalar carriers. That made the compiler emit nearly the
right local instruction topology, but it was compensating for an incorrect
whole-function allocation state.

The exact source instead uses the natural loop:

```c
for (i3 = 0; i3 < AQ_LIMB_MAX; i3++) {
    sAqBacoonlimbTimers[i3] = 50;
}
```

It becomes the target's four-store unrolled loop only after the rest of the
function has the correct variable roles and live ranges. Important global
changes include:

- removing the overloaded `i` local and adding a distinct `i6`;
- using `i7` for the common animation-table index;
- reordering and reusing floating-point locals;
- preserving nested assignment trees with explicit parentheses and casts;
- spelling arithmetic grouping explicitly where IDO's expression trees care.

The key conclusion is that a locally convincing match can still represent a
false source topology. When a small region needs increasingly artificial
fakes, test whether upstream live ranges and variable-role reuse are wrong
before continuing to mutate that region.

## Regional-ROM proof

The linked Aquas function in Japan rev 0, USA rev 0, and USA rev 1 has the same
3032-instruction opcode and register structure. Differences are linked
addresses/immediates only. This ruled out a regional source branch and made
the USA rev 1 target valid as the structural oracle for all three ROMs.

## Public tooling backlog

1. Add cross-ROM linked-function comparison which masks linked addresses and
   immediates even when ELF relocation metadata is unavailable.
2. Add whole-function variable-role and live-range visualization. Highlight
   locals reused in distant regions and show how a local source edit changes
   allocator colors globally.
3. Extend compiler temporary traces so type-4 temps map back to their source
   expression and symbol. The current `line=-1` records make allocator webs
   such as `w625` and `w627` hard to identify.
4. Add a "false local minimum" warning: if a natural loop is replaced by
   unrolling, fake carriers, or repeated opaque uses while the residual
   mismatch remains allocation-heavy, recommend a whole-function topology
   pass.
5. Add source-diff experiment attribution: given an exact source and a
   near-match, bisect groups of declaration, expression-tree, loop, and
   variable-role changes and report which groups alter each mismatch range.
6. Preserve exact compiler-sensitive examples as regression fixtures,
   including the natural case-18 loop and the nested `u32` assignment tree.
