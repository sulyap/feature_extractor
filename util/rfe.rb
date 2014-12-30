#!/usr/bin/env ruby
# Tool to call feature extractor programs on a directory of jpg files
# Syntax: ruby rfe.rb [DIR] [filename] [feature_type]
# Possible feature types:
#   - glcm
#   - lbp

def syntax
  puts "rfe.rb [DIR] [filename] [feature_type] [label]"
end

FEATURE_TYPES = ["glcm", "lbp"]

# Location of glcm executable
GLCM_EXE = "./glcm"

# Location of lbp executable
LBP_EXE = "./lbp"

# error checking
if ARGV.length != 4
  syntax
  abort
end

directory = ARGV[0]
filename = ARGV[1]
feature_type = ARGV[2]
label = ARGV[3]

if !FEATURE_TYPES.include?(feature_type)
  puts "Invalid feature type #{feature_type}"
  abort
end

# create file for writing
file = File.new(filename, "a")

Dir.glob("#{directory}/*.jpg") do |item|
  exe = ""
  if feature_type == "glcm"
    exe = GLCM_EXE
  elsif feature_type == "lbp"
    exe = LBP_EXE
  end

  puts "Filename: #{item}"
  feature_vector = `#{exe} #{item}`
  file << "#{label},#{feature_vector}"
  #puts "Writing data to #{filename}..."
  #puts "#{label}: #{feature_vector}"
end

file.close
