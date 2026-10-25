#!/bin/bash
# P294: ray survivors (P291) with the far scenes, then ledge mutants
S=docs/port/sessions/p294; cd ~/conker-wt/pe
$S/muts.sh $S/ray_surv_hmuts.txt $S/hmut_ray.log 300 -- --only ray
$S/muts.sh $S/ledge_hmuts.txt $S/hmut_ledge.log 300 -- --only ac8c4
