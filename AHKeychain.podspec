Pod::Spec.new do |s|
  s.name = 'AHKeychain'
  s.version = '0.1.1'
  s.platform = :osx
  s.license = 'MIT'
  s.summary = 'Objective-c class for managing os x keychains'
  s.homepage = 'https://github.com/eahrold/AHKeychain'
  s.authors  = { 'Eldon Ahrold' => 'eldon.ahrold@gmail.com' }
  s.source   = { :git => 'https://github.com/eahrold/AHKeychain.git', :tag => "#{s.version}" }
  s.requires_arc = true  
  s.frameworks = 'Security', 'Foundation'
  s.public_header_files = 'AHKeychain/*.h'
  s.source_files = 'AHKeychain/*.{h,m}'
end
  