
Pod::Spec.new do |s|
  s.name         = "RNStarPrnt"
  s.version      = "1.0.0"
  s.summary      = "RNStarPrnt"
  s.description  = <<-DESC
                  RNStarPrnt
                   DESC
  s.homepage     = "https://github.com/infoxicator/react-native-star-prnt"
  s.license      = "MIT"
  # s.license      = { :type => "MIT", :file => "FILE_LICENSE" }
  s.author             = { "author" => "author@domain.cn" }
  s.platform     = :ios, "7.0"
  s.source       = { :git => "https://github.com/author/RNStarPrnt.git", :tag => "master" }
  s.source_files  = "ios/**/*.{h,m}"
  s.requires_arc = true


  s.dependency "React"
  s.frameworks = 'CoreBluetooth', 'ExternalAccessory'
  s.vendored_frameworks = 'ios/Frameworks/StarIO.framework', 'ios/Frameworks/StarIO_Extension.framework'

  #s.dependency "others"

end

  
