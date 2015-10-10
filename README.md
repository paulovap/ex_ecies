# ExEcies

**TODO: Add description**

## Installation

If [available in Hex](https://hex.pm/docs/publish), the package can be installed as:

  1. Add ex_ecies to your list of dependencies in `mix.exs`:

        def deps do
          [{:ex_ecies, "~> 0.0.2"}]
        end

  2. Ensure ex_ecies is started before your application:

        def application do
          [applications: [:ex_ecies]]
        end

## Troubleshooting

### OS X users

* Must use openssl from brew
* Make sure the system libraries point to brew's install of openssl (it must be a better solution to this)
```
    sudo mv /usr/bin/openssl /usr/bin/openssl_OLD
    sudo mv libssl.dylib OLDlibssl.dylib
    sudo mv libcrypto.dylib OLDlibcrypto.dylib
    sudo ln -s /usr/local/Cellar/openssl/1.0.2d_1 /usr/bin/openssl
    sudo ln -s  /usr/bin/openssl/lib/libssl.dylib
    sudo ln -s  /usr/bin/openssl/lib/libcrypto.dylib
```
