{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
  };
  outputs = {
    self,
    nixpkgs,
  }: let
    system = "x86_64-linux";
    pkgs = import nixpkgs {inherit system;};
  in {
    packages.${system}.default = pkgs.stdenv.mkDerivation (finalAttrs: {
      name = "poo-simulation";

      src = ./.;

      nativeBuildInputs = with pkgs; [
        cmake
        libsForQt5.wrapQtAppsHook
      ];
      buildInputs = with pkgs; [
        libsForQt5.qtbase
      ];

      installPhase = ''
        runHook preInstall

        mkdir -p $out/bin
        cp ./Simulation $out/bin/poo-simulation

        runHook postInstall
      '';
    });
  };
}
