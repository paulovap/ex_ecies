defmodule ExEciesTest do
  use ExUnit.Case
  doctest ExEcies

  test "the truth" do
  	text = "holy smokes! It worked!"
    {pub, priv} = ExEcies.generate_key
  	x = ExEcies.encrypt pub, text 
  	^text = ExEcies.decrypt priv, x
  end
end
