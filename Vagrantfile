# -*- mode: ruby -*-
# vi: set ft=ruby :

def gui_enabled?
  !ENV.fetch('VAGRANT_GUI', '').empty?
end

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
        libc++{1,-dev,-helpers,abi-dev,abi1} \
        libgl{,u}1-mesa-dev \
        libqt5scintilla2-{12v5,dev,l10n} \
        llvm-3.8 \
        mesa-common-dev \
        qt57{{charts,datavis}-no-lgpl,scxml} \
        qt5{6,7}{3d,base,canvas3d,graphicaleffects,imageformats,multimedia,quickcontrols{,2},tools} \
        upx-ucl \
        xvfb \

      git clone -q https://github.com/g-truc/glm
      cd ./glm
      cmake .
      make install
      git clean -xdf
      cd ..

      git clone -q https://github.com/ilmola/generator
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
    osx.vm.box = "AndrewDryga/vagrant-box-osx"
    osx.vm.hostname = "osx"
    osx.vm.network "forwarded_port", guest: 22, host: 2202, auto_correct: true

    osx.vm.provider "virtualbox" do |vb|
      vb.gui = gui_enabled?
      vb.memory = "2048"
      vb.linked_clone = true if Vagrant::VERSION =~ /^1.8/
      vb.cpus = 1 # OSX guests can't have more than one CPU right now
      vb.customize ["modifyvm", :id, "--accelerate3d", "off"] # See https://github.com/AndrewDryga/vagrant-box-osx#common-issues
    end

    osx.vm.synced_folder ".", "/vagrant", type: "rsync",
      rsync__exclude: ".vagrant/",
      rsync__args: ["--rsync-path='sudo rsync'"]

    osx.vm.provision "shell", privileged: false, inline: <<-SHELL
      brew install boost binutils git upx cmake gcc qt5 wget rsync qscintilla2
      brew linkapps qt5
      git clone -q https://github.com/g-truc/glm
      cd ./glm
      cmake .
      make install
      git clean -xdf
      cd ..

      git clone -q https://github.com/ilmola/generator
      cd ./generator
      cmake -DGENERATOR_USE_GLM=True -DGENERATOR_SUFFIX_GLM=True -DCMAKE_BUILD_TYPE=Release
      make install
      git clean -xdf
      cd ..
    SHELL
  end

  config.vm.define "win8" do |win8|
    win8.vm.box = "JesseTG/win8-balls"
    win8.vm.communicator = "winrm"
    win8.vm.network "forwarded_port", guest: 22, host: 2203, auto_correct: true
    win8.vm.boot_timeout = 600
    win8.vm.graceful_halt_timeout = 600

    win8.vm.provider "virtualbox" do |vb|
      vb.gui = gui_enabled?
      vb.memory = "2048"
      vb.linked_clone = true if Vagrant::VERSION =~ /^1.8/
    end

    win8.vm.provision "shell", inline: <<-SHELL
      choco upgrade all -y

      git clone -q https://github.com/g-truc/glm
      cd ./glm
      cmake .
      make install
      git clean -xdf
      cd ..

      git clone -q https://github.com/ilmola/generator
      cd ./generator
      cmake -DGENERATOR_USE_GLM=True -DGENERATOR_SUFFIX_GLM=True -DCMAKE_BUILD_TYPE=Release
      make install
      git clean -xdf
      cd ..
    SHELL
  end

  # TODO: consider Microsoft/EdgeOnWindows10 if this one is a problem
  config.vm.define "win10" do |win10|
    win10.vm.box = "JesseTG/win10-balls"
    win10.vm.communicator = "winrm"
    win10.vm.network "forwarded_port", guest: 22, host: 2204, auto_correct: true
    win10.vm.boot_timeout = 600
    win10.vm.graceful_halt_timeout = 600

    win10.vm.provider "virtualbox" do |vb|
      vb.gui = gui_enabled?
      vb.memory = "2048"
      vb.linked_clone = true if Vagrant::VERSION =~ /^1.8/
    end

    win10.vm.provision "shell", inline: <<-SHELL
      choco upgrade all -y
    SHELL
  end
end
