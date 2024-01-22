#! /bin/bash

# Linux
rustup target add x86_64-unknown-linux-gnu
rustup target add i686-unknown-linux-gnu
cargo build --target x86_64-unknown-linux-gnu --release
cargo build --target i686-unknown-linux-gnu --release

# macOS
rustup target add x86_64-apple-darwin
cargo build --target x86_64-apple-darwin --release

# Windows (MSVC)
rustup target add x86_64-pc-windows-msvc
rustup target add i686-pc-windows-msvc
cargo build --target x86_64-pc-windows-msvc --release
cargo build --target i686-pc-windows-msvc --release

# Windows (GNU)
rustup target add x86_64-pc-windows-gnu
rustup target add i686-pc-windows-gnu
cargo build --target x86_64-pc-windows-gnu --release
cargo build --target i686-pc-windows-gnu --release

# BSD
rustup target add x86_64-unknown-freebsd
rustup target add i686-unknown-freebsd
rustup target add x86_64-unknown-netbsd
rustup target add i686-unknown-netbsd
cargo build --target x86_64-unknown-freebsd --release
cargo build --target i686-unknown-freebsd --release
cargo build --target x86_64-unknown-netbsd --release
cargo build --target i686-unknown-netbsd --release

# Others
rustup target add aarch64-unknown-linux-gnu
rustup target add armv7-unknown-linux-gnueabihf
rustup target add wasm32-unknown-unknown
cargo build --target aarch64-unknown-linux-gnu --release
cargo build --target armv7-unknown-linux-gnueabihf --release
cargo build --target wasm32-unknown-unknown --release