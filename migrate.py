import os
import shutil
import re

# Исходная и целевая директории
SRC_ROOT = r"mcgw"
DST_ROOT = r"launcher"

# Новая структура
STRUCTURE = {
    "include": [
        "network.h", "json_utils.h", "version.h", "manifest.h",
        "auth.h", "game.h", "utils.h", "gui.h"
    ],
    "src": [
        "main.cpp", "network.c", "json_utils.c", "version.c", "manifest.c",
        "auth.c", "game.c", "utils.c", "gui.cpp"
    ],
    "libs/cjson": ["cJSON.c", "cJSON.h", "cJSON_Utils.c", "cJSON_Utils.h"],
    "libs/zlib": ["miniz.c", "miniz.h"],
    "libs/other_libs": ["sha1.c", "sha1.h", "ws2_32.Lib"],
    "build/objs": [],
    "build": ["launcher.exe"],
    "res/icons": [],
    "res/fonts": [],
    "res/lang": [],
    "cache/versions": [],
    "cache/assets": [],
    "cache": ["manifest.json"],
}

# Переименование файлов
RENAME = {
    "cJSON.c": "json_utils.c",
    "cJSON.h": "json_utils.h",
    "cJSON_Utils.c": "json_utils.c",
    "cJSON_Utils.h": "json_utils.h",
    "network.cpp": "network.c",
    "utils.cpp": "utils.c",
    "version_manifest.json": "manifest.json",
    "mcgw.exe": "launcher.exe",
}

# Файлы для создания, если их нет
EMPTY_FILES = [
    "include/version.h", "include/manifest.h", "include/auth.h", "include/game.h", "include/gui.h",
    "src/version.c", "src/manifest.c", "src/auth.c", "src/game.c", "src/gui.cpp"
]

def ensure_dirs():
    for path in STRUCTURE:
        os.makedirs(os.path.join(DST_ROOT, path), exist_ok=True)

def move_and_rename(src_dir, dst_dir, files):
    for fname in files:
        src_path = os.path.join(SRC_ROOT, src_dir, fname)
        if not os.path.exists(src_path):
            continue
        new_name = RENAME.get(fname, fname)
        dst_path = os.path.join(DST_ROOT, dst_dir, new_name)
        shutil.copy2(src_path, dst_path)

def migrate_files():
    # include
    move_and_rename("include", "include", [
        "cJSON.h", "cJSON_Utils.h", "httplib.h", "miniz.h", "sha1.h"
    ])
    move_and_rename("src", "include", [
        "network.h", "utils.h", "log.h"
    ])
    # src
    move_and_rename("src", "src", [
        "main.cpp", "network.cpp", "utils.cpp", "log.c"
    ])
    # libs
    move_and_rename("include", "libs/cjson", [
        "cJSON.h", "cJSON_Utils.h"
    ])
    move_and_rename("include", "libs/zlib", [
        "miniz.h"
    ])
    move_and_rename("include", "libs/other_libs", [
        "sha1.h"
    ])
    move_and_rename("src", "libs/cjson", [
        "cJSON.c", "cJSON_Utils.c"
    ])
    move_and_rename("src", "libs/zlib", [
        "miniz.c"
    ])
    move_and_rename("src", "libs/other_libs", [
        "sha1.c"
    ])
    move_and_rename("lib", "libs/other_libs", [
        "ws2_32.Lib"
    ])
    # bin
    move_and_rename("bin", "build", [
        "mcgw.exe"
    ])
    # objs
    objs_dir = os.path.join(SRC_ROOT, "bin", "objs")
    if os.path.exists(objs_dir):
        for f in os.listdir(objs_dir):
            shutil.copy2(os.path.join(objs_dir, f), os.path.join(DST_ROOT, "build/objs", f))
    # manifest
    move_and_rename("bin", "cache", [
        "version_manifest.json"
    ])
    # Makefile
    move_and_rename("bin", "", [
        "Makefile"
    ])
    # README
    move_and_rename("", "", [
        "sum.md"
    ])

def create_empty_files():
    for rel_path in EMPTY_FILES:
        full_path = os.path.join(DST_ROOT, rel_path)
        if not os.path.exists(full_path):
            open(full_path, "w").close()

def update_includes():
    # Обновить пути #include во всех .c/.cpp/.h
    for root, _, files in os.walk(os.path.join(DST_ROOT, "src")):
        for fname in files:
            if fname.endswith(('.c', '.cpp', '.h')):
                fpath = os.path.join(root, fname)
                with open(fpath, "r", encoding="utf-8", errors="ignore") as f:
                    content = f.read()
                # Заменить старые пути на новые
                content = re.sub(r'#include\s+"cJSON(_Utils)?\.h"', '#include "json_utils.h"', content)
                content = re.sub(r'#include\s+"utils\.h"', '#include "utils.h"', content)
                content = re.sub(r'#include\s+"network\.h"', '#include "network.h"', content)
                content = re.sub(r'#include\s+"log\.h"', '#include "utils.h"', content)
                with open(fpath, "w", encoding="utf-8") as f:
                    f.write(content)

def main():
    ensure_dirs()
    migrate_files()
    create_empty_files()
    update_includes()
    print("Migration complete! Проверьте структуру launcher/.")

if __name__ == "__main__":
    main()