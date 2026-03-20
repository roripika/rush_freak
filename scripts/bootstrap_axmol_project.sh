#!/usr/bin/env bash
set -euo pipefail

if ! command -v axmol >/dev/null 2>&1; then
    echo "error: axmol command was not found." >&2
    echo "Install/setup Axmol first, then re-run this script." >&2
    exit 1
fi

output_dir="${1:-build/axmol_port}"
package_name="${AXMOL_PACKAGE_NAME:-dev.roripika.rushfreak}"
project_name="${AXMOL_PROJECT_NAME:-rush_freak_axmol}"

mkdir -p "${output_dir}"
axmol new -p "${package_name}" -d "${output_dir}" -l cpp "${project_name}"

cat <<MSG

Axmol project scaffold created at:
  ${output_dir}/${project_name}

Next manual steps:
  1. Copy rendaPower/Classes/*.h and *.cpp into ${output_dir}/${project_name}/Source/
  2. Copy rendaPower/Resources/* into ${output_dir}/${project_name}/Content/
  3. Merge the updated AppDelegate/scene sources, then run:
       axmol build -p <platform> -c
MSG
