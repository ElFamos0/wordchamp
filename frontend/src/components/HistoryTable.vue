<template>
  <div>
    <div v-for="entry in entries" :key="entry.id">
        <div>
          <HistoryEntry @show-details="showDetails"
          :entryId="entry.id" :solution="entry.solution" :result="entry.result"
          />
        </div>
        <div>
          <DetailedEntry v-if="entry.detailsToggled" :entryId="entry.id" :solution="entry.solution" :result="entry.result" :guesses="entry.guesses" :maxtry="entry.maxtry"/>
          <br>
        </div>
    </div>
  </div>
</template>


<script>
import HistoryEntry from './HistoryEntry.vue'
import DetailedEntry from '../components/DetailedEntry.vue'

export default {
  name: 'HistoryTable',
  props: {
      entries: Array
  },
  components: {
    HistoryEntry,
    DetailedEntry,
  },
  emits: ['show-details'],
  methods: {
      showDetails(entryId) {
        console.log("vous avez cliqué sur l'entrée ", entryId, " toggle valait ", this.entries[entryId].detailsToggled)
        this.entries[entryId].detailsToggled=!this.entries[entryId].detailsToggled
      }
  },
  data() {
    // let toggled = {}
    // console.log('entriesssss', this.entries)
    // console.log('toggleeeeee', toggled)
    // for (var entry in this.entries) {
    //   const cle = entry.id
    //   console.log("cle",cle)
    //   toggled[cle]=entry.detailsToggled
    //   console.log(toggled)
    // }   
    return {
        // toggled: toggled
    }
  },
  created() {
  }
}

</script>

<style scoped>

</style>