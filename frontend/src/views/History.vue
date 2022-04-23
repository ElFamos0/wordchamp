<template>
    <div>
        <h1>Historique</h1>
        <history-table @show-details="showDetails" :entries="entries"/>
    </div>
</template>


<script>
import HistoryTable from '../components/HistoryTable.vue'

export default {
  name: 'History',
  props: {
  },
  components: {
    HistoryTable,
  },
  emits: ['show-details'],
  data() {
      return {
          entries:[
              {id:"1", motFinal:"Oulala", result:"Victoire"},
              {id:"2", motFinal:"MaitreSauceur", result:"Défaite"},
              {id:"3", motFinal:"sérieuxmec", result:"NULMDR"},
              {id:"4", motFinal:"sheeeeeeeeeeeeeeeeeeesh", result:"Défiak"},
          ]
      }
  },
  methods: {
      showDetails(entryId) {
        console.log("vous avez cliqué sur l'entrée : ", entryId)
      }
  }
}
</script>

<style scoped>

</style>