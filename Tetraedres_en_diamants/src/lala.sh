#!/bin/bash
for i in {1..20}
do
   echo "../data/out$i.mesh";
   ./main "../data/out$i.mesh";
done
