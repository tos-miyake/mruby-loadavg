class Loadavg

  def loadavg_1
    read_loadavg.split[0].to_f
  end

  def loadavg_5
    read_loadavg.split[1].to_f
  end

  def loadavg_15
    read_loadavg.split[3].to_f
  end

  private def read_loadavg
    IO.read('/proc/loadavg')
  end
end
