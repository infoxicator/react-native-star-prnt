
Pod::Spec.new do |s|
  s.name         = "RNStarPrnt"
  s.version      = "1.0.0"
  s.summary      = "RNStarPrnt"
  s.description  = <<-DESC
                  RNStarPrnt
                   DESC
  s.homepage     = ""
  s.license      = "MIT"
  # s.license      = { :type => "MIT", :file => "FILE_LICENSE" }
  s.author             = { "author" => "author@domain.cn" }
  s.platform     = :ios, "7.0"
  s.source       = { :git => "https://github.com/author/RNStarPrnt.git", :tag => "master" }
  s.source_files  = "RNStarPrnt/**/*.{h,m}"
  s.requires_arc = true


  s.dependency "React"
  s.vendored_frameworks = 'StarIO.framework'
  s.vendored_frameworks = 'StarIO_Extension.framework'

  #s.dependency "others"

end

  