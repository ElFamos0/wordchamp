<template>
    <div style="padding-top: 1%">
        <h1 style="font-family: 'Roboto', sans-serif">Historique des parties</h1>
        <history-table :entries="entries" style="margin-bottom: 5%"/>
    </div>
</template>


<script>
import HistoryTable from '../components/HistoryTable.vue'
import axiosAuth from '@/api/axios-auth'

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
    axiosAuth.get(path).then((res)=> {
      this.entries = res.data.entries
    })
  },
}
</script>

<style scoped>

</style>