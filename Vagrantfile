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
    ubuntu.vm.box = "ubuntu/xenial64"

    # TODO: Put together a list of packages instead of wild-carding qt56, so
    # everything installs faster
    ubuntu.vm.provision "shell", inline: <<-SHELL
      wget -O - http://apt.llvm.org/llvm-snapshot.gpg.key|sudo apt-key add -
      sudo add-apt-repository -y ppa:beineri/opt-qt561-xenial
      sudo add-apt-repository -y 'deb http://apt.llvm.org/xenial/ llvm-toolchain-xenial main'
      sudo apt-get update
      sudo apt-get dist-upgrade -y
      sudo apt-get install -y qt56* git cmake clang-3.8 llvm-3.8
    SHELL
  end

  config.vm.define "osx" do |osx|
    osx.vm.box = "jhcook/osx-elcapitan-10.11"

    osx.vm.provider "virtualbox" do |vb|
      vb.gui = false
      vb.memory = "2048"
    end
  end

  config.vm.define "win8" do |win8|
    win8.vm.box = "opentable/win-2012r2-standard-amd64-nocm"
    win8.vm.boot_timeout = 600

    win8.vm.provider "virtualbox" do |vb|
      vb.gui = false
      vb.memory = "2048"
      vb.linked_clone = true if Vagrant::VERSION =~ /^1.8/
    end

    win8.vm.provision "shell", inline: <<-SHELL
      iwr https://chocolatey.org/install.ps1 -UseBasicParsing | iex
      choco install -y cygwin cyg-get cmake git mingw upx
    SHELL
  end

  # TODO: consider Microsoft/EdgeOnWindows10 if this one is a problem
  config.vm.define "win10" do |win10|
    win10.vm.box = "senglin/win-10-enterprise-vs2015community"

    win10.vm.provider "virtualbox" do |vb|
      vb.gui = false
      vb.memory = "2048"
    end
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
