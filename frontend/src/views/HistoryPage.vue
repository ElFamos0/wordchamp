<template>
    <div>
        <h1>Historique</h1>
        <history-table :entries="entries"/>
    </div>
</template>


<script>
import HistoryTable from '../components/HistoryTable.vue'
import axios from 'axios';

export default {
  name: 'HistoryPage',
  props: {
  },
  components: {
    HistoryTable,
  },
  emits: ['show-details'],
  data() {
    return {
      entries:[]
      }
  },
  created() {
      const path = `${process.env.VUE_APP_BACKEND_URL}/history`
      axios.get(path).then((res)=> {
        this.entries = res.data.entries
      })
  },
}
</script>

<style scoped>

</style>