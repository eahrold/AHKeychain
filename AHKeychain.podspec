Pod::Spec.new do |s|
  s.name = 'AHLaunchCtl'
  s.version = '0.1'
  s.license = 'MIT'
  s.summary = 'Objective-c class for managing os x keychains'
  s.homepage = 'https://github.com/eahrold/AHKeychain'
  s.authors  = { 'Eldon Ahrold' => 'eldon.ahrold@gmail.com' }
  s.source   = { :git => 'https://github.com/eahrold/AHKeychain.git', :tag => "v#{s.version}" }
  s.requires_arc = true  
  s.public_header_files = 'AHKeychain/*.h'
  s.source_files = 'AHLaunchCtl/*.{h,m}'
  s.frameworks = 'Security', 'Foundation'
end
  