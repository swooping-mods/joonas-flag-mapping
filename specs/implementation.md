# J.O.O.N.A.S. Flag Mapping: behavior and implementation

Describes the retained payload **0.1.0**. The behavior prose describes the retained payload; current candidate source and metadata are identified below. Gameplay qualification is a separate requirement.


<!-- source-only-sync -->
## Current source candidate

Source version **0.1.0** is saved from workshop revision `ca32bbf79ce0840d5166a232bdb3a9fdcd761254`. The retained installable payload remains **0.1.0** with its original bytes. This source update does not rebuild or requalify that payload. The current source and metadata define the candidate; gameplay, rendered behavior and co-op remain unqualified for rebuilt bytes.

The authored behavior and lifecycle descriptions below are retained from the published payload. They are not new qualification evidence for the source candidate. The integration table below follows the current candidate metadata.
<!-- /source-only-sync -->

## Behavior

Scans up to 64 loaded J.O.O.N.A.S. rigs on the host at one-second intervals. A robot must belong to the current world; nearby native flag/site discoveries set bounded known-landmark bits. When the native map opens, those known landmarks receive globe markers oriented from the world direction and globe radius. The feature augments discovery display rather than issuing robot movement orders.

## State and lifecycle

Known discoveries use the checked per-world/player sidecar. Host authority is latched and dirty save state retries; guest code does not become a writer after disconnect. Map marker roots are temporary and removed on map/world ownership changes.

## Integration and configuration

No additional feature-mod runtime dependency is declared. Included shared headers are source reuse, not extra DLL dependencies.

The [module metadata](../source/mods/joonas-flag-mapping/mod.json) owns the version and declared integration contract. Native modules start at `MoonLab_ModStart`. Game/Unity integrations target the pinned Steam Windows x64 IL2CPP build.

## Implementation sources

- [mod.c](../source/mods/joonas-flag-mapping/mod.c)
- [runtime.h](../source/mods/joonas-flag-mapping/runtime.h)
- [store.h](../source/mods/joonas-flag-mapping/store.h)

## Verification boundary

Only loaded robot rigs and bounded native landmark data are observed. No remote off-scene scouting or guest command protocol is added. Discovery radius, markers and save round trips require native-game checks.

`python3 build.py --check` verifies the exported source hashes. It does not execute the mod or qualify the behaviors above. Installation and independent build prerequisites are in the [README](../README.md).
