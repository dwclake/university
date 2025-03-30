defmodule Convert do
  def from_decimal(decimal, base, result \\ [])
  def from_decimal(0, _, result) do
    Enum.join result
  end

  def from_decimal(decimal, base, result) do
    quotient = div(decimal, base)
    rem = rem(decimal, base)
    result = [rem | result]

    from_decimal(quotient, base, result)
  end
end

args = System.argv
decimal =
  Enum.at(args, 0, "100")
    |> String.to_integer
base =
  Enum.at(args, 1, "2")
    |> String.to_integer

IO.puts "#{decimal} in base #{base} is: #{Convert.from_decimal(decimal, base)}"
