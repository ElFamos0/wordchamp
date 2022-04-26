<template>
<div>
    <div><h1>yo les bggggg ici c le classement</h1></div> 
        <v-simple-table
            fixed-header
            height="300px">
            <template v-slot:default>
                <thead>
                    <tr>
                    <th class="text-left">
                        Classement   
                    </th>
                    <th class="text-left">
                        Pseudo
                    </th>
                    <th class="text-left">
                        Points
                    </th>
                    </tr>
                </thead>
                <tbody>
                    <tr
                    v-for="userData in usersData"
                    :key="userData.classement"
                    >
                    <td>{{ userData.classement }}</td>
                    <td>{{ userData.username }}</td>
                    <td>{{ userData.points }}</td> 
                    </tr>
                </tbody>
            </template>
        </v-simple-table>
    <!-- <div v-for="userData in usersData" :key="userData.index">salut mec</div>  -->
</div>
</template>

<script>
import axios from '@/api/axios-auth'

export default {
    classement: 'ClassementPage',
    data () {
        return {
            usersData: [],
            }
    },
    created() {
        axios.get(path).then((res)=> {
            res.data.users.forEach(element => {
                
                this.usersData.push(element);
            });
            })
    },
}
const path = `${process.env.VUE_APP_BACKEND_URL}/classement`;

</script>

<style scoped>
</style>