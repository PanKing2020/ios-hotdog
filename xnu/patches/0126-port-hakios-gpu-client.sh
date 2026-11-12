#!/bin/bash
# The GPU client: the IOKit node a Metal/GLES userland reaches (HakiosGPU + its user client) and the
# IOSurface stand-in the window server hands surfaces through. Both are taken from the HakiOS tree at
# a pinned commit; the driver half (bsd/dev/sweet_gpu_adreno.c) grew the hakios_gpu_* calls they make.
set -euo pipefail

[[ "${MACHINE_CONFIG:-}" == GUACAMOLE || "${MACHINE_CONFIG:-}" == SWEET ]] || exit 0

sha=57722468a3774e2ec60017705ec356ae9b31f40e
base="https://raw.githubusercontent.com/HeliumStudio-Dev/hackios-xnu-kernel/${sha}/xnu/files/iokit/Kernel"

for f in hakios.gpu.cpp MiniIOSurface.cpp MiniIOSurface.h MiniDrivers.h; do
	curl -fsSL "${base}/${f}" -o "iokit/Kernel/${f}"
	echo "fetched iokit/Kernel/${f} ($(wc -c < "iokit/Kernel/${f}") bytes)"
done

python3 - <<'PY'
from pathlib import Path

conf = Path("iokit/conf/files")
text = conf.read_text()
if "hakios.gpu.cpp" in text:
    raise SystemExit(0)
lines = text.split("\n")
for i, line in enumerate(lines):
    if line.startswith("iokit/Kernel/IOPlatformExpert.cpp"):
        lines[i + 1:i + 1] = [
            "iokit/Kernel/MiniIOSurface.cpp\t\t\toptional iokitcpp",
            "iokit/Kernel/hakios.gpu.cpp\t\t\t\toptional iokitcpp",
        ]
        break
else:
    raise SystemExit("iokit/conf/files: no IOPlatformExpert.cpp line")
conf.write_text("\n".join(lines))
print("iokit/conf/files: MiniIOSurface.cpp and hakios.gpu.cpp added")
PY
