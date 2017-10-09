class Light < ApplicationRecord
  def red
    { "action": "red" }
  end

  def yellow
    { "action": "yellow" }
  end

  def green
    { "action": "green" }
  end

  def on
    { "action": "on" }
  end

  def off
    { "action": "off" }
  end

  def nothing
    { "action": "nothing" }
  end
end
