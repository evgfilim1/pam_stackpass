# pam_stackpass

A simple C library to get or put passwords from/to PAM stack.

I made this module to use it together with [google/google-authenticator-libpam][gauthpam]
to be able to enter either OTP or my linux user password.

## Building & Installing

### Requirements
- cmake
- pam

```shell
git clone https://github.com/evgfilim1/pam_stackpass
cd pam_stackpass
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=/usr .. && make && sudo make install
```

## Usage

### Simple usage

```
auth    required    pam_stackpass.so    prompt
auth    required    pam_stackpass.so    echo
```

### Real-world example

_/etc/pam.d/system-auth_
```
auth       required                    pam_faillock.so      preauth
-auth      [success=4 default=ignore]  pam_systemd_home.so
auth       required                    pam_stackpass.so     prompt
auth       [success=2 default=ignore]  pam_google_authenticator.so use_first_pass nullok
auth       [success=1 default=bad]     pam_unix.so          use_first_pass nullok
#auth       required                    pam_stackpass.so     echo
auth       [default=die]               pam_faillock.so      authfail
```

[gauthpam]: https://github.com/google/google-authenticator-libpam
