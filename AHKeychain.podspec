Pod::Spec.new do |spec|
  spec.name = 'AHKeychain'
  spec.version = '0.2'
  spec.platform = :osx
  spec.license = 'MIT'
  spec.summary = 'Objective-c class for managing os x keychains'
  spec.homepage = 'https://github.com/eahrold/AHKeychain'
  spec.authors  = { 'Eldon Ahrold' => 'eldon.ahrold@gmail.com' }
  spec.source   = { :git => 'https://github.com/eahrold/AHKeychain.git', :tag => "v#{spec.version}" }
  spec.requires_arc = true
  spec.frameworks = 'Security', 'Foundation'
  spec.public_header_files = 'AHKeychain/*.h'
  spec.source_files = 'AHKeychain/*.{h,m}'
end
