# -*- mode: ruby -*-
# vi: set ft=ruby :

# All Vagrant configuration is done below. The "2" in Vagrant.configure
# configures the configuration version (we support older styles for
# backwards compatibility). Please don't change it unless you know what
# you're doing.
Vagrant.configure(2) do |config|
  # The most common configuration options are documented and commented below.
  # For a complete reference, please see the online documentation at
  # https://docs.vagrantup.com.

  config.vm.define "ubuntu" do |ubuntu|
    ubuntu.vm.box = "bento/ubuntu-16.04"
    ubuntu.vm.hostname = "ubuntu"
    ubuntu.vm.network "forwarded_port", guest: 22, host: 2201, auto_correct: true
    ubuntu.vm.provider "virtualbox" do |vb|
      vb.gui = false
      vb.memory = "2048"
      vb.linked_clone = true if Vagrant::VERSION =~ /^1.8/
    end

    ubuntu.vm.provision "shell", inline: <<-SHELL
      apt-get update -q
      apt-get install -qy software-properties-common
      wget -nv -O llvm.key http://apt.llvm.org/llvm-snapshot.gpg.key 2>&1
      apt-key add llvm.key 2>&1
      rm llvm.key
      apt-mark hold grub*
      add-apt-repository -y ppa:beineri/opt-qt561-xenial
      add-apt-repository -y ppa:beineri/opt-qt57-xenial
      add-apt-repository -y 'deb http://apt.llvm.org/xenial/ llvm-toolchain-xenial main'
      apt-get update -q
      apt-get dist-upgrade -qy
      apt-get install -qy \
        clang-3.8 \
        cmake \
        cmake-extras \
        extra-cmake-modules \
        g++ \
        git \
        libboost-all-dev \
        libqt5scintilla2-{12v5,dev,l10n} \
        libc++{1,-dev,-helpers,abi-dev,abi1} \
        llvm-3.8 \
        mesa-common-dev \
        qt57{{charts,datavis}-no-lgpl,scxml} \
        qt5{6,7}{3d,base,canvas3d,graphicaleffects,imageformats,multimedia,quickcontrols{,2},tools} \
        upx-ucl \
        xvfb \

      git clone https://github.com/g-truc/glm
      cd ./glm
      cmake .
      make install
      git clean -xdf
      cd ..

      git clone https://github.com/ilmola/generator
      cd ./generator
      cmake -DGENERATOR_USE_GLM=True -DGENERATOR_SUFFIX_GLM=True -DCMAKE_BUILD_TYPE=Release
      make install
      git clean -xdf
      cd ..
    SHELL
  end

  # TODO: Try jhcook/osx-elcapitan-10.11
  # TODO: Try ferranvila/osx-elcapitan
  config.vm.define "osx" do |osx|
    osx.vm.box = "jhcook/osx-elcapitan-10.11"
    osx.vm.hostname = "osx"
    osx.vm.network "forwarded_port", guest: 22, host: 2202, auto_correct: true

    osx.vm.provider "virtualbox" do |vb|
      vb.gui = false
      vb.memory = "2048"
      vb.linked_clone = true if Vagrant::VERSION =~ /^1.8/
    end

    osx.vm.provision "shell", privileged: false, inline: <<-SHELL
      /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
      brew install git upx cmake gcc qt5 wget
    SHELL
  end

  config.vm.define "win8" do |win8|
    win8.vm.box = "JesseTG/win8-balls"
    win8.vm.hostname = "win8"
    win8.vm.network "forwarded_port", guest: 22, host: 2203, auto_correct: true
    win8.vm.boot_timeout = 600
    win8.vm.graceful_halt_timeout = 600

    win8.vm.provider "virtualbox" do |vb|
      vb.gui = false
      vb.memory = "2048"
      vb.linked_clone = true if Vagrant::VERSION =~ /^1.8/
    end

    win8.vm.provision "shell", inline: <<-SHELL
      choco upgrade all -y
    SHELL
  end

  # TODO: consider Microsoft/EdgeOnWindows10 if this one is a problem
  config.vm.define "win10" do |win10|
    win10.vm.box = "JesseTG/win10-balls"
    win10.vm.hostname = "win10"
    win10.vm.network "forwarded_port", guest: 22, host: 2204, auto_correct: true
    win10.vm.boot_timeout = 600
    win10.vm.graceful_halt_timeout = 600

    win10.vm.provider "virtualbox" do |vb|
      vb.gui = false
      vb.memory = "2048"
      vb.linked_clone = true if Vagrant::VERSION =~ /^1.8/
    end

    win10.vm.provision "shell", inline: <<-SHELL
      choco upgrade all -y
    SHELL
  end


  # Create a forwarded port mapping which allows access to a specific port
  # within the machine from a port on the host machine. In the example below,
  # accessing "localhost:8080" will access port 80 on the guest machine.
  # config.vm.network "forwarded_port", guest: 80, host: 8080

  # Create a private network, which allows host-only access to the machine
  # using a specific IP.
  # config.vm.network "private_network", ip: "192.168.33.10"

  # Create a public network, which generally matched to bridged network.
  # Bridged networks make the machine appear as another physical device on
  # your network.
  # config.vm.network "public_network"

  # Share an additional folder to the guest VM. The first argument is
  # the path on the host to the actual folder. The second argument is
  # the path on the guest to mount the folder. And the optional third
  # argument is a set of non-required options.
  # config.vm.synced_folder "../data", "/vagrant_data"

  # Provider-specific configuration so you can fine-tune various
  # backing providers for Vagrant. These expose provider-specific options.
  # Example for VirtualBox:
  #

  #
  # View the documentation for the provider you are using for more
  # information on available options.

  # Enable provisioning with a shell script. Additional provisioners such as
  # Puppet, Chef, Ansible, Salt, and Docker are also available. Please see the
  # documentation for more information about their specific syntax and use.
end
