package main

import "sort"

type Counters struct {
	Name       string
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

func OrderCountersByAverage() []*Counters {
	var ordered []*Counters
	for _, counter := range statCounters {
		ordered = append(ordered, counter)
	}
	sort.Slice(ordered, func(i, j int) bool {
		return ordered[i].WinCount > ordered[j].WinCount
	})
	return ordered
}
