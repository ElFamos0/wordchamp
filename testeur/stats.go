package main

type Counters struct {
	WinCount   int
	Total      int
	AverageTry float64
}

var statCounters map[string]*Counters

func init() {
	statCounters = make(map[string]*Counters)
}

func (c *Counters) UpdateAverage(tries int) {
	if c.AverageTry == 0 {
		c.AverageTry = float64(tries)
	} else {
		c.AverageTry = c.AverageTry*float64(c.Total-1)/float64(c.Total) + float64(tries)/float64(c.Total)
	}
}
