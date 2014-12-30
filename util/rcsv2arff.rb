#!/usr/bin/env ruby
# Tool to convert csv file to arff for Weka. Works only for numeric data.
# Assumes last column as label
# Syntax: rcsv2arff.rb [input.csv] [output.csv] [relation]

def syntax
  puts "rcsv2arff.rb [input.csv] [output.csv] [relation]"
end

if ARGV.length != 3
  puts "Error! Invalid number of arguments"
  syntax
  abort
end

INPUT_CSV = ARGV[0]
OUTPUT_ARFF = ARGV[1]
RELATION = ARGV[2]

# number of dimensions. set after first read
n = 0

input_file = File.new(INPUT_CSV, "r")
n = input_file.readline.split(",").length
input_file.close

puts "Number of dimensions: #{n}"
puts "Generating header..."

output_file = File.new(OUTPUT_ARFF, "a")
output_file.puts "@RELATION #{RELATION}"

n.times do |i|
  if i == 0
    output_file.puts "@ATTRIBUTE class NUMERIC"
  else
    output_file.puts "@ATTRIBUTE x#{i} NUMERIC"
  end
end

# generate data
puts "Generating data..."
output_file.puts "@DATA"
input_file = File.new(INPUT_CSV, "r")
while(line = input_file.gets)
  output_file.puts line
end
input_file.close

output_file.close

puts "Done..."
