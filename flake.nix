{
  inputs = {
    nixpkgs = {
      url = "github:nixos/nixpkgs/nixos-unstable";
    };
    flake-utils = {
      url = "github:numtide/flake-utils";
    };
  };
  outputs = { nixpkgs, flake-utils, ... }: flake-utils.lib.eachDefaultSystem (system:
    let
      pkgs = import nixpkgs {
        inherit system;
      };
      rss-cli = (with pkgs; stdenv.mkDerivation {
          pname = "rss-cli";
          version = "master";
          src = fetchgit {
            url = "https://github.com/Clortox/rss-cli";
            rev = "e28bb8f66e941274b02cbc5ac5f28483bc26d588";
            sha256 = "sha256-AWFkgIOrNjfdBAWa1EC5J26SP4EH3RfkXosRXpe3yPI=";
          };
          nativeBuildInputs = [
            pkg-config
          ];
          buildInputs = [
            curl.dev
            rapidxml
          ];
          buildPhase = "make all -j $NIX_BUILD_CORES";
          installPhase = ''
          mkdir --parents "$out/bin"
          cp bin/* $out/bin
          '';
        }
      );
    in rec {
      defaultApp = flake-utils.lib.mkApp {
        drv = defaultPackage;
      };
      defaultPackage = rss-cli;
      devShell = pkgs.mkShell {
        buildInputs = [
          rss-cli
        ];
      };
    }
  );
}
