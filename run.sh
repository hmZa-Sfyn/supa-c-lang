#!/bin/bash

set -e  # Exit immediately if a command exits with a non-zero status
set -u  # Treat unset variables as an error
set -o pipefail  # Catch errors in piped commands

# Define installation paths
INSTALL_DIR="/usr/local/bin/supac"
BIN_DIR="$INSTALL_DIR/bin"
LIBS_DIR="$INSTALL_DIR/libs"
ENV_FILE="$INSTALL_DIR/supac.env"

# Ensure root privileges
if [[ $EUID -ne 0 ]]; then
  echo "This script must be run as root! Use sudo." >&2
  exit 1
fi

# Create necessary directories if they don't exist
mkdir -p "$BIN_DIR" "$LIBS_DIR"

# Copy files safely
echo "Copying necessary files..."
install -m 755 ./supac "$BIN_DIR/"
install -m 644 -D ./assets "$INSTALL_DIR/assets"
install -m 644 -D ./stdlib "$LIBS_DIR/"
install -m 755 ./bin/supac_pm "$BIN_DIR/"
install -m 755 ./bin/supac_langmang "$BIN_DIR/"

# Create environment file
echo "Setting up environment..."
echo "LANGUAGE::VERSION=1.1" > "$ENV_FILE"
echo "LANGUAGE::IS_BETA=True" >> "$ENV_FILE"

# Copy run script safely
if [[ -f "./run.sh" ]]; then
  install -m 755 ./run.sh "$INSTALL_DIR/supac.sh"i

# Add aliases safely to .bashrc and .zshrc
for shell_config in ~/.bashrc ~/.zshrc; do
  if [[ -f "$shell_config" ]]; then
    grep -qxF "alias supacc='$BIN_DIR/supac'" "$shell_config" || echo "alias supacc='$BIN_DIR/supac'" >> "$shell_config"
    grep -qxF "alias supac='$BIN_DIR/supac_langmang'" "$shell_config" || echo "alias supac='$BIN_DIR/supac_langmang'" >> "$shell_config"
    grep -qxF "alias scpm='$BIN_DIR/supac_pm'" "$shell_config" || echo "alias papm='$BIN_DIR/supac_pm'" >> "$shell_config"
  fi
done

# Success message
echo "Installation completed successfully! Please restart your terminal or run: source ~/.bashrc or source ~/.zshrc"
