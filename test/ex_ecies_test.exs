defmodule ExEciesTest do
  use ExUnit.Case
  doctest ExEcies

  test "the truth" do
  	text = "holy smokes! It worked!"
    {pub, priv} = ExEcies.generate_key
  	^text = text |> ExEcies.encrypt(pub) |> ExEcies.decrypt(priv)
  end
end
