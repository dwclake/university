def div(a : Int, b : Int)
  quotient = a.tdiv(b)
  rem = a.remainder(b)

  return {quotient, rem}
end

struct Int
  def to_hex : String
    case self
      when 0...9; "#{self}"
      when 10...15; (self + 55).chr.to_s
      else "0"
    end
  end
end

def from_decimal(decimal : Int, into : Int, result = [] of String) : String
  # Base case when decimal is 0
  return result.join if decimal <= 0

  quotient, rem = div(decimal, into)
  result.unshift(rem.to_hex)
  # Recursive call, passing the quotient as the new decimal
  from_decimal(quotient, into, result)
end

decimal, base = {
  ARGV[0]?.try &.to_i || 100, 
  ARGV[1]?.try &.to_i.clamp(2, 16) || 2
}

puts "#{decimal} in base #{base} is: #{from_decimal decimal, into: base} \u{1F631}"
