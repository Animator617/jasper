PROCESSOR_ARCHITECTURE
@echo off

set "language=de"

IF "%language%" == "de" (
    goto languageDE
) ELSE (
    IF "%language%" == "en" (
        goto languageEN
    ) ELSE (
    echo Not found.
    )
)

:languageEN
:languageDE

echo %language%
